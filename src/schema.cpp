#include "schema.h"

#include <doctest/doctest.h>

namespace inamorata {

Schema::Schema(std::istream &schema) {
  const auto node = YAML::Load(schema);

  m_root = node["root"];
  m_types = node["types"].as<decltype(m_types)>();
}

auto Schema::type(const std::string &type) -> const YAML::Node * {
  const auto node = m_types.find(type);

  if (node != m_types.end()) {
    return &node->second;
  }

  return nullptr;
}

} // namespace inamorata
