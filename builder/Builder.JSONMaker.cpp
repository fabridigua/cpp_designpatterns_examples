#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <memory>
using namespace std;

struct JSONBuilder;

struct JSONData
{
    std::string key;
    std::string value;  
    std::vector<JSONData> elements;    

  JSONData() {}
  JSONData(const string& key, const string& value)
    : key(key), value(value), elements({})
  {}
  JSONData(const string& key, const std::vector<JSONData>& elements)
    : key(key), elements(elements), value(std::string())
  {}

  string str(int indent = 0) const
  {
    string _indent(2*indent, ' ');

    ostringstream oss;

    //  if(key.empty()) oss << "{" << std::endl;

    if(!key.empty())
        oss << _indent << "\"" << key << "\" : ";
    if(!value.empty())
    {
        oss << value << "," << std::endl;
    }
    else
    {
        oss << " { " << std::endl;
            for (auto& data: elements)
            {
                oss << _indent << data.str();
            }
        oss << " } " << std::endl;
    }
    
    // if(key.empty()) oss << "}" << std::endl;

    return oss.str();
  }

  static unique_ptr<JSONBuilder> build()
  {
    return make_unique<JSONBuilder>();
  }
};

struct JSONBuilder
{
  JSONBuilder()
  {
    root.key = "";
  }

  JSONBuilder& add_str(string child_key, string child_value)
  {
    JSONData e{ child_key, "\""+child_value+"\"" };
    root.elements.emplace_back(e);
    return *this;
  }
  
  JSONBuilder& add_int(string child_key, int child_value)
  {
    JSONData e{ child_key, std::to_string(child_value) };
    root.elements.emplace_back(e);
    return *this;
  }
  
  JSONBuilder& add_bool(string child_key, bool child_value)
  {
    JSONData e{ child_key, (child_value?"true":"false") };
    root.elements.emplace_back(e);
    return *this;
  }
  
  JSONBuilder& add_obj(string child_key, JSONBuilder& obj)
  {
    JSONData e{ child_key, obj.root.elements };
    root.elements.emplace_back(e);
    return *this;
  }

  string str() { return root.str(); }

  operator JSONData() const { return root; }
  JSONData root;
};

int main()
{
  JSONBuilder json_obj_builder;
  json_obj_builder.add_bool("message_sent", false)
  .add_int("length", 7)
  .add_str("author", "kant");
  
  JSONBuilder json_obj_root;
  json_obj_root.add_str("id", "id-aodjd-djjf-kodo")
  .add_bool("success", false)
  .add_bool("isRelease", true)
  .add_int("counter", 42)
  .add_obj("details", json_obj_builder);

  JSONBuilder builder;
  builder.add_obj("test", json_obj_root)
  .add_int("timestamp", 17284932)
  .add_bool("debug_mode", true);
  std::cout << builder.str() << std::endl;


  getchar();
  return 0;
}