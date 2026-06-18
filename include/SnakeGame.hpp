#pragma once

#include <deque>
#include <random>
#include <string>

#include "ftxui/dom/elements.hpp"

class SnakeGame {
 public:
  static constexpr int kBoardWidth = 30;
  static constexpr int kBoardHeight = 18;

  SnakeGame();

  void Reset();
  void Tick();
  void TurnUp();
  void TurnDown();
  void TurnLeft();
  void TurnRight();
  void TogglePause();

  bool IsGameOver() const;
  bool IsPaused() const;
  int Score() const;
  int TickIntervalMs() const;

  ftxui::Element Render() const;

 private:
  struct Point {
    int x = 0;
    int y = 0;

    bool operator==(const Point& other) const {
      return x == other.x && y == other.y;
    }
  };

  enum class Direction {
    Up,
    Down,
    Left,
    Right,
  };

  void ChangeDirection(Direction next);
  Point NextHead() const;
  bool IsOpposite(Direction next) const;
  bool ContainsSnake(const Point& point) const;
  void PlaceFood();
  ftxui::Element RenderBoard() const;
  ftxui::Element RenderCell(const Point& point) const;
  ftxui::Element RenderStats() const;

  std::deque<Point> snake_;
  Point food_;
  Direction direction_ = Direction::Right;
  Direction pending_direction_ = Direction::Right;
  int score_ = 0;
  bool game_over_ = false;
  bool paused_ = false;
  std::mt19937 rng_;
};
