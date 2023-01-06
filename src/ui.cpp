#include "ui.hpp"

using namespace pandaboygba;
static int scale = 4;
static sf::Clock myClock;
static sf::Color tile_colors[5] = { sf::Color::White, sf::Color(170, 170, 170), sf::Color(85, 85, 85), sf::Color::Black, sf::Color::Magenta };

static void fillRect(sf::Image* target, const sf::IntRect& rect, const sf::Color& color) {
  for (int y = rect.top; y < rect.top + rect.height; y++)
    for (int x = rect.left; x < rect.left + rect.width; x++)
      {
	target->setPixel(x, y, color);
      }
}

pbg_ui::pbg_ui(pbg_context *ctx)
  : _context_ptr(ctx), _ticks(0), _window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Emulator"),
    _debugWindow(sf::VideoMode((16 * 8 * scale) + (16 * scale), (32 * 8 * scale) + (64 * scale)), "Debug Window")
{
  std::cout << "🎮 " << RED << "[" << ORANGE << "Running UI!" << RED << "]" << DEFAULT << " 🎮" << std::endl;
  this->_window.setVerticalSyncEnabled(true);
  this->_window.setFramerateLimit(30);
  this->_windowRenderTexture.create(SCREEN_WIDTH, SCREEN_HEIGHT);
  this->_windowScreen.create(SCREEN_WIDTH, SCREEN_HEIGHT, sf::Color(0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000));
  this->_debugRenderTexture.create((16 * 8 * scale) + (16 * scale), (32 * 8 * scale) + (64 * scale));
  this->_debugScreen.create((16 * 8 * scale) + (16 * scale), (32 * 8 * scale) + (64 * scale), sf::Color(0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000));
  sf::Vector2i position = this->_window.getPosition();
  this->_debugWindow.setPosition(sf::Vector2i(position.x + SCREEN_WIDTH + 10, position.y));
  myClock.restart();
}

sf::RenderWindow& pbg_ui::get_window(void)
{
  return this->_window;
}

void pbg_ui::window_stop(void)
{
  this->_window.close();
}

void pbg_ui::delay(uint32_t time)
{
  sf::sleep(sf::milliseconds(time));
}

void	pbg_ui::setTicks(uint64_t state)
{
  this->_ticks = state;
  this->_ticks = myClock.getElapsedTime().asMilliseconds();
}

uint64_t	pbg_ui::getTicks()	const
{
  return myClock.getElapsedTime().asMilliseconds();
}

void pbg_ui::ui_update()
{
  uint32_t* video_buffer = ppu_get_context()->video_buffer;
  this->_windowScreen.create(SCREEN_WIDTH, SCREEN_HEIGHT, sf::Color::Transparent);
  for (int line_num = 0; line_num < YRES; line_num++) {
    for (int x = 0; x < XRES; x++) {
      sf::IntRect rc;
      rc.left = x * scale;
      rc.top = line_num * scale;
      rc.width = scale;
      rc.height = scale;
      uint32_t pixel = video_buffer[x + (line_num * XRES)];
      sf::Color color;
      color.a = ((pixel & 0xFF000000) >> 24);
      color.r = ((pixel & 0x00FF0000) >> 16);
      color.g = ((pixel & 0x0000FF00) >> 8);
      color.b = ((pixel & 0x000000FF));
      fillRect(&_windowScreen, rc, color);
    }
  }
  sf::Texture texture;
  texture.loadFromImage(_windowScreen); // load image data into texture
  sf::Sprite sprite(texture); // create sprite from texture
  _windowRenderTexture.draw(sprite); // draw sprite on render texture
  _windowRenderTexture.display();
  _windowTexture = _windowRenderTexture.getTexture();
  sf::Sprite spriteText(_windowTexture);
  _window.draw(spriteText);
  _window.display();
  update_dbg_window();

}

void pbg_ui::update_dbg_window()
{
  int xDraw = 0;
  int yDraw = 0;
  int tileNum = 0;
  uint16_t addr = 0x8000;
  //384 tiles, 24 x 16
  for (int y = 0; y < 24; y++)
    {
      for (int x = 0; x < 16; x++)
	{
	  this->display_tile(&this->_debugScreen, addr, tileNum, xDraw + (x * scale), yDraw + (y * scale));
	  xDraw += (8 * scale);
	  tileNum++;
	}
      yDraw += (8 * scale);
      xDraw = 0;
    }
  sf::Texture texture;
  texture.loadFromImage(this->_debugScreen);
  this->_debugRenderTexture.draw(sf::Sprite(texture));
  this->_debugRenderTexture.display();
  this->_debugTexture = this->_debugRenderTexture.getTexture();
  this->_debugWindow.draw(sf::Sprite(this->_debugTexture));
  this->_debugWindow.display();
}

void pbg_ui::display_tile(sf::Image *surface, uint16_t startLocation, uint16_t tileNum, int x, int y)
{
  sf::Rect<int> rc;
  for (int tileY=0; tileY<16; tileY += 2)
    {
      uint8_t b1 = this->_context_ptr->_bus_ptr->bus_read(startLocation + (tileNum * 16) + tileY);
      uint8_t b2 = this->_context_ptr->_bus_ptr->bus_read(startLocation + (tileNum * 16) + tileY + 1);
      for (int bit=7; bit >= 0; bit--)
	{
	  uint8_t hi = !!(b1 & (1 << bit)) << 1;
	  uint8_t lo = !!(b2 & (1 << bit));
	  uint8_t color = hi | lo;
	  rc.left = x + ((7 - bit) * scale);
	  rc.top = y + (tileY / 2 * scale);
	  rc.width = scale;
	  rc.height = scale;
	  fillRect(surface, rc, (tile_colors[color]));
	}
    }
}

void pbg_ui::ui_on_key(bool down, sf::Keyboard::Key key_code)
{
  switch(key_code) {
  case sf::Keyboard::A: this->_context_ptr->_gamepad_ptr->gamepad_get_state()->b = down; break;
  case sf::Keyboard::B: this->_context_ptr->_gamepad_ptr->gamepad_get_state()->a = down; break;
  case sf::Keyboard::R: this->_context_ptr->_gamepad_ptr->gamepad_get_state()->start = down; break;
  case sf::Keyboard::E: this->_context_ptr->_gamepad_ptr->gamepad_get_state()->select = down; break;
  case sf::Keyboard::Z: this->_context_ptr->_gamepad_ptr->gamepad_get_state()->up = down; break;
  case sf::Keyboard::S: this->_context_ptr->_gamepad_ptr->gamepad_get_state()->down = down; break;
  case sf::Keyboard::D: this->_context_ptr->_gamepad_ptr->gamepad_get_state()->left = down; break;
  case sf::Keyboard::Q: this->_context_ptr->_gamepad_ptr->gamepad_get_state()->right = down; break;
  }
}

void pbg_ui::ui_on_joystick(bool down, sf::Joystick::Axis axis, unsigned int joystick)
{
  gamepad_state* state = this->_context_ptr->_gamepad_ptr->gamepad_get_state();
  switch(axis) 
    {
    case sf::Joystick::Axis::X:
      if (down) 
	{
	  state->left = sf::Joystick::getAxisPosition(joystick, sf::Joystick::Axis::X) < -50.0f;
	  state->right = sf::Joystick::getAxisPosition(joystick, sf::Joystick::Axis::X) > 50.0f;
	} 
      else 
	{
	  state->left = false;
	  state->right = false;
	}
      break;
    case sf::Joystick::Axis::Y:
      if (down) 
	{
	  state->up = sf::Joystick::getAxisPosition(joystick, sf::Joystick::Axis::Y) < -50.0f;
	  state->down = sf::Joystick::getAxisPosition(joystick, sf::Joystick::Axis::Y) > 50.0f;
	} 
      else 
	{
	  state->up = false;
	  state->down = false;
	}
      break;
    }
}

void pbg_ui::ui_on_joystick_btn(sf::Joystick::Axis axis, unsigned int joystick)
{
  gamepad_state* state = this->_context_ptr->_gamepad_ptr->gamepad_get_state();
  if (sf::Joystick::isButtonPressed(joystick, 0))
    state->a = true;
  else state->a = false;
  if (sf::Joystick::isButtonPressed(joystick, 1))
    state->b = true;
  else state->b = false;
  if (sf::Joystick::isButtonPressed(joystick, 11))
    state->start = true;
  else state->start = false;
  if (sf::Joystick::isButtonPressed(joystick, 10))
    state->select = true;
  else state->select = false;
    
}
