#pragma once

#include <yaml-cpp/yaml.h>

#include <istream>
#include <optional>
#include <string>
#include <unordered_map>

namespace inamorata {

class Schema {
public:
  explicit Schema(std::istream &schema);

  auto type(const std::string &type) -> const YAML::Node *;

private:
  YAML::Node m_root;
  std::unordered_map<std::string, YAML::Node> m_types;
};

} // namespace inamorata
