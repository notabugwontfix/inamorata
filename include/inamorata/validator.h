#pragma once

#include <istream>
#include <memory>

namespace inamorata {

class Schema;

class Validator {
public:
  explicit Validator(const std::istream &schema);

  void validate(const std::istream &yaml);

private:
  const std::unique_ptr<Schema> m_schema;
};

} // namespace inamorata
