#include <atomic>
#include <chrono>
#include <thread>

#include "SnakeGame.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/event.hpp"
#include "ftxui/component/screen_interactive.hpp"

int main() {
  using namespace ftxui;

  SnakeGame game;
  auto screen = ScreenInteractive::FitComponent();
  std::atomic<bool> running = true;

  auto renderer = Renderer([&] { return game.Render(); });

  auto component = CatchEvent(renderer, [&](Event event) {
    if (event == Event::Character('q') || event == Event::Character('Q') ||
        event == Event::Escape) {
      running = false;
      screen.ExitLoopClosure()();
      return true;
    }

    if (event == Event::Custom) {
      game.Tick();
      return true;
    }

    if (event == Event::Character('a') || event == Event::Character('A') ||
        event == Event::ArrowLeft) {
      game.TurnLeft();
      return true;
    }
    if (event == Event::Character('d') || event == Event::Character('D') ||
        event == Event::ArrowRight) {
      game.TurnRight();
      return true;
    }
    if (event == Event::Character('s') || event == Event::Character('S') ||
        event == Event::ArrowDown) {
      game.TurnDown();
      return true;
    }
    if (event == Event::Character('w') || event == Event::Character('W') ||
        event == Event::ArrowUp) {
      game.TurnUp();
      return true;
    }
    if (event == Event::Character('p') || event == Event::Character('P')) {
      game.TogglePause();
      return true;
    }
    if (event == Event::Character('r') || event == Event::Character('R')) {
      game.Reset();
      return true;
    }

    return false;
  });

  std::thread timer([&] {
    while (running) {
      std::this_thread::sleep_for(
          std::chrono::milliseconds(game.TickIntervalMs()));
      screen.PostEvent(Event::Custom);
    }
  });

  screen.Loop(component);
  running = false;
  screen.PostEvent(Event::Custom);

  if (timer.joinable()) {
    timer.join();
  }

  return 0;
}
