#pragma once

#include <istream>

namespace inamorata {

class Validator {
public:
  explicit Validator(const std::istream &schema);

  void validate(const std::istream &yaml);

private:
  const std::istream &m_schema;
};

} // namespace inamorata
