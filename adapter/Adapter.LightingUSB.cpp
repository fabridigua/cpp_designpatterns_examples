#include <string>
#include <regex>
#include <iostream>

// The Target interface: you only need the interface
class USBC_reader {
 public:
  virtual ~USBC_reader() = default;

  virtual std::string read_data() const {
    // [...] Real reading logic
    return "[Reader]: Receiving data from device..";
  }
};

// Adaptee: 
class Lighting_reader {
 public:
  std::string read_from_apple_device() const {
    // [...] Real reading logic
    return "[Apple Reader]: Receiving data from device..";
  }
};

// Adapter:take a Lighting reader and use it as a USBC reader
class LightingUSBCAdapter : public USBC_reader {
 private:
  Lighting_reader *_adaptee;

 public:
  LightingUSBCAdapter(Lighting_reader *adaptee) : _adaptee(adaptee) {}

  std::string read_data() const override {
    std::string lighting_data = this->_adaptee->read_from_apple_device();

    std::string search("Apple ");
      for (std::string::size_type i = lighting_data.find(search);
      i != std::string::npos;
      i = lighting_data.find(search))
      lighting_data.erase(i, search.length());

    std::string to_usbc_data = lighting_data;
    return "LightingUSBCAdapter: " + to_usbc_data;
  }
};

// Client Code supporting (only) the Target object (USB-C)
void Client(const USBC_reader *targetReader) {
    // [...]
  std::cout << targetReader->read_data();
}

// Usage Example
int main() {
  USBC_reader *target = new USBC_reader;  
  
  std::cout << "Target reads like this: " << std::endl;
  Client(target);
  
  Lighting_reader *adaptee = new Lighting_reader;
  std::cout << "\nAdaptee reads like this: " << adaptee->read_from_apple_device() << std::endl;

  std::cout << "But now the Client Code can work also with an Adaptee trough the Adapter." << std::endl;
  LightingUSBCAdapter *adapter = new LightingUSBCAdapter(adaptee);
  Client(adapter);
  
  delete target;
  delete adaptee;
  delete adapter;

  return 0;
}