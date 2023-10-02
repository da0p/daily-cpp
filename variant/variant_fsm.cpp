#include <cassert>
#include <iostream>
#include <variant>

struct DoorState
{
  struct DoorOpened
  {};
  struct DoorClosed
  {};
  struct DoorLocked
  {};

  using State = std::variant<DoorOpened, DoorClosed, DoorLocked>;

  void open() { m_state = std::visit(OpenEvent{}, m_state); }

  void close() { m_state = std::visit(CloseEvent{}, m_state); }

  void lock() { m_state = std::visit(LockEvent{}, m_state); }

  void unlock() { m_state = std::visit(UnlockEvent{}, m_state); }

  struct OpenEvent
  {
    State operator()(DoorOpened const&) { return DoorOpened(); }
    State operator()(DoorClosed const&) { return DoorOpened(); }
    State operator()(DoorLocked const&) { return DoorLocked(); }
  };

  struct CloseEvent
  {
    State operator()(DoorOpened const&) { return DoorClosed(); }
    State operator()(DoorClosed const&) { return DoorClosed(); }
    State operator()(DoorLocked const&) { return DoorLocked(); }
  };

  struct LockEvent
  {
    State operator()(DoorOpened const&) { return DoorOpened(); }
    State operator()(DoorClosed const&) { return DoorLocked(); }
    State operator()(DoorLocked const&) { return DoorLocked(); }
  };

  struct UnlockEvent
  {
    State operator()(DoorOpened const&) { return DoorOpened(); }
    State operator()(DoorClosed const&) { return DoorClosed(); }
    State operator()(DoorLocked const&) { return DoorClosed(); }
  };

  State m_state;
};

int
main()
{
  DoorState s;
  assert(std::holds_alternative<DoorState::DoorOpened>(s.m_state));
  s.lock();
  assert(std::holds_alternative<DoorState::DoorOpened>(s.m_state));
  s.close();
  assert(std::holds_alternative<DoorState::DoorClosed>(s.m_state));
  s.lock();
  assert(std::holds_alternative<DoorState::DoorLocked>(s.m_state));
  s.open();
  assert(std::holds_alternative<DoorState::DoorLocked>(s.m_state));

  return 0;
}