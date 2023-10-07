#include <iostream>

class DataPacket
{
  std::string data_;
  size_t checkSum_;
  size_t serverId_;

public:
  DataPacket()
    : data_{}
    , checkSum_{0}
    , serverId_{0}
  {
  }

  explicit DataPacket(std::string const& data, size_t serverId)
    : data_{data}
    , checkSum_{calcCheckSum(data)}
    , serverId_{serverId}
  {
  }

  DataPacket(DataPacket const& other)
    : data_{other.data_}
    , checkSum_{other.checkSum_}
    , serverId_{other.serverId_}
  {
    std::cout << "Copy ctor for \"" << data_ << "\"\n";
  }

  DataPacket(DataPacket&& other) noexcept
    : data_{std::move(other.data_)} // move string member...
    , checkSum_{other.checkSum_}
    , serverId_{other.serverId_}
  {
    other.checkSum_ = 0;
    std::cout << "Move ctor for \"" << data_ << "\"\n";
  }

  DataPacket& operator=(DataPacket const& other)
  {
    if(this != &other) {
      data_ = other.data_;
      checkSum_ = other.checkSum_;
      serverId_ = other.serverId_;
      std::cout << "Assignment for \"" << data_ << "\"\n";
    }
    return *this;
  }

  DataPacket& operator=(DataPacket&& other) noexcept
  {
    if(this != &other) {
      data_ = std::move(other.data_);
      checkSum_ = other.checkSum_;
      other.checkSum_ = 0; // leave this in a proper state
      serverId_ = other.serverId_;
      std::cout << "Move assignment for \"" << data_ << "\"\n";
    }
    return *this;
  }

  size_t calcCheckSum(std::string const& data) { return 0; }

  std::string getData() const { return data_; }

  size_t getCheckSum() const { return checkSum_; }
};

int
main()
{
  DataPacket firstMsg{"first msg", 101};
  DataPacket copyMsg{firstMsg};

  DataPacket secondMsg{"second msg", 202};
  copyMsg = secondMsg;

  DataPacket movedMsg{std::move(secondMsg)};
  // now we stole the data, so it should be empty...
  std::cout << "secondMsg's data after move ctor):\"" << secondMsg.getData()
            << "\", sum: " << secondMsg.getCheckSum() << "\n";

  movedMsg = std::move(firstMsg);

  // now we stole the name, so it should be empty...
  std::cout << "firstMsg's data after move ctor): \"" << firstMsg.getData()
            << "\", sum: " << firstMsg.getCheckSum() << "\n";
}