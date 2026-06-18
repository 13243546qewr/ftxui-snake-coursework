#include "SnakeGame.hpp"

#include <algorithm>
#include <chrono>

#include "ftxui/dom/elements.hpp"

using ftxui::bgcolor;
using ftxui::bold;
using ftxui::border;
using ftxui::center;
using ftxui::color;
using ftxui::Color;
using ftxui::Element;
using ftxui::flex;
using ftxui::hbox;
using ftxui::paragraph;
using ftxui::separator;
using ftxui::text;
using ftxui::vbox;

SnakeGame::SnakeGame()
    : rng_(static_cast<unsigned int>(
          std::chrono::steady_clock::now().time_since_epoch().count())) {
  Reset();
}

void SnakeGame::Reset() {
  snake_.clear();
  const int center_x = kBoardWidth / 2;
  const int center_y = kBoardHeight / 2;

  snake_.push_back({center_x, center_y});
  snake_.push_back({center_x - 1, center_y});
  snake_.push_back({center_x - 2, center_y});

  direction_ = Direction::Right;
  pending_direction_ = Direction::Right;
  score_ = 0;
  game_over_ = false;
  paused_ = false;
  PlaceFood();
}

void SnakeGame::Tick() {
  if (game_over_ || paused_) {
    return;
  }

  direction_ = pending_direction_;
  const Point head = NextHead();

  if (head.x < 0 || head.x >= kBoardWidth || head.y < 0 ||
      head.y >= kBoardHeight) {
    game_over_ = true;
    return;
  }

  const bool will_eat = head == food_;
  if (!will_eat) {
    snake_.pop_back();
  }

  if (ContainsSnake(head)) {
    game_over_ = true;
    return;
  }

  snake_.push_front(head);

  if (will_eat) {
    score_ += 10;
    PlaceFood();
  }
}

void SnakeGame::TurnUp() {
  ChangeDirection(Direction::Up);
}

void SnakeGame::TurnDown() {
  ChangeDirection(Direction::Down);
}

void SnakeGame::TurnLeft() {
  ChangeDirection(Direction::Left);
}

void SnakeGame::TurnRight() {
  ChangeDirection(Direction::Right);
}

void SnakeGame::TogglePause() {
  if (!game_over_) {
    paused_ = !paused_;
  }
}

bool SnakeGame::IsGameOver() const {
  return game_over_;
}

bool SnakeGame::IsPaused() const {
  return paused_;
}

int SnakeGame::Score() const {
  return score_;
}

int SnakeGame::TickIntervalMs() const {
  const int speed_bonus = score_ / 50 * 15;
  return std::max(70, 180 - speed_bonus);
}

Element SnakeGame::Render() const {
  auto title = text("FTXUI Snake") | bold | center;
  auto body = hbox({
      RenderBoard(),
      separator(),
      vbox({
          RenderStats(),
          separator(),
          paragraph("W/A/S/D or arrows: move  P: pause  R: restart  Q: quit"),
      }) | flex,
  });

  if (game_over_) {
    return vbox({
               title,
               body,
               text("Game Over - press R to restart or Q to quit") | bold |
                   color(Color::Red) | center,
           }) |
           border;
  }

  if (paused_) {
    return vbox({
               title,
               body,
               text("Paused - press P to continue") | bold |
                   color(Color::Yellow) | center,
           }) |
           border;
  }

  return vbox({title, body}) | border;
}

void SnakeGame::ChangeDirection(Direction next) {
  if (!game_over_ && !paused_ && !IsOpposite(next)) {
    pending_direction_ = next;
  }
}

SnakeGame::Point SnakeGame::NextHead() const {
  Point head = snake_.front();

  switch (direction_) {
    case Direction::Up:
      head.y--;
      break;
    case Direction::Down:
      head.y++;
      break;
    case Direction::Left:
      head.x--;
      break;
    case Direction::Right:
      head.x++;
      break;
  }

  return head;
}

bool SnakeGame::IsOpposite(Direction next) const {
  return (direction_ == Direction::Up && next == Direction::Down) ||
         (direction_ == Direction::Down && next == Direction::Up) ||
         (direction_ == Direction::Left && next == Direction::Right) ||
         (direction_ == Direction::Right && next == Direction::Left);
}

bool SnakeGame::ContainsSnake(const Point& point) const {
  return std::find(snake_.begin(), snake_.end(), point) != snake_.end();
}

void SnakeGame::PlaceFood() {
  std::uniform_int_distribution<int> x_distribution(0, kBoardWidth - 1);
  std::uniform_int_distribution<int> y_distribution(0, kBoardHeight - 1);

  do {
    food_ = {x_distribution(rng_), y_distribution(rng_)};
  } while (ContainsSnake(food_));
}

Element SnakeGame::RenderBoard() const {
  std::vector<Element> rows;
  rows.reserve(kBoardHeight);

  for (int y = 0; y < kBoardHeight; ++y) {
    std::vector<Element> cells;
    cells.reserve(kBoardWidth);
    for (int x = 0; x < kBoardWidth; ++x) {
      cells.push_back(RenderCell({x, y}));
    }
    rows.push_back(hbox(std::move(cells)));
  }

  return vbox(std::move(rows)) | border;
}

Element SnakeGame::RenderCell(const Point& point) const {
  if (point == food_) {
    return text("  ") | bgcolor(Color::Red);
  }

  if (!snake_.empty() && point == snake_.front()) {
    return text("  ") | bgcolor(Color::GreenLight);
  }

  if (ContainsSnake(point)) {
    return text("  ") | bgcolor(Color::Green);
  }

  return text("  ") | bgcolor(Color::Black);
}

Element SnakeGame::RenderStats() const {
  return vbox({
      text("Score: " + std::to_string(score_)),
      text("Length: " + std::to_string(snake_.size())),
      text("Speed: " + std::to_string(1000 / TickIntervalMs()) + " cells/s"),
  });
}
