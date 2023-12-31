#include <string>
#include <vector>
#include <iostream>
#include <sstream>

namespace JSON 
{

    const int INDENT = 2;

    class JSONData
    {
        protected:
            std::string key;
            std::string value;      
            
        public:
             friend std::ostream& operator<<(std::ostream& os, const JSONData& data)
            {
                os << "\"" << data.key << "\" : " << data.value;
                return os;
            }
            JSONData(const std::string& key): key(key), value("undefined"){};
            JSONData(const std::string& key, const std::string& value): key(key), value(value){};
    };

    class INT: public JSONData {
        public: INT(std::string key, int value):JSONData(key,std::to_string(value)){}
    };
    class FLOAT: public JSONData {
        public: FLOAT(std::string key, float value):JSONData(key,std::to_string(value)){}
    };
    class BOOL: public JSONData {
        public: BOOL(std::string key, bool value):JSONData(key, (value?"true":"false")){};
    };
    class STR: public JSONData {
        public: STR(std::string const key, std::string const value):JSONData(key, "\""+value+"\""){}
    };
    class _NULL: JSONData {
        public: _NULL(std::string key):JSONData(key, "null"){}
    };
    class OBJ: public JSONData {
        std::vector<JSONData> _elements;

        public:
            explicit OBJ(std::string const key, std::initializer_list<JSONData> elements):JSONData(key)
            {
                _elements = elements;

                std::ostringstream oss;
                oss << "{" << std::endl;
                for(int k=0; k < _elements.size(); k++)
                {
                    oss << std::string(INDENT,' ');
                    oss << _elements[k] << ((k + 1 < _elements.size()) ? ",":"") << std::endl ;
                }
                oss << "}";

                this->value = oss.str();
            };
    };

}

int main()
{
  std::cout <<  
        JSON::OBJ{ "test", {
            JSON::STR{"id", "id-aodjd-djjf-kodo"},
            JSON::BOOL{"success", false},
            JSON::BOOL{"isRelease", true},
            JSON::INT{"counter", 42},
            JSON::OBJ{ "details", {
                JSON::BOOL{"message_sent", false},
                JSON::INT{"length", 7},
                JSON::STR{"author", "kant"}
            }}
        }};
  getchar();
  return 0;
}