#include "gtest/gtest.h"
#include "config_parser.h"
#include <sstream>
#include <string>

// basic test using example_config file
TEST(NginxConfigParserTest, SimpleConfig) {
  NginxConfigParser parser;
  NginxConfig out_config;

  bool success = parser.Parse("example_config", &out_config);

  EXPECT_TRUE(success);
}

// test ToString
TEST(NginxConfigStatementTest, ToString) {
    NginxConfigStatement statement;
    statement.tokens_.push_back("foo");
    statement.tokens_.push_back("bar");
    EXPECT_EQ("foo bar;\n", statement.ToString(0));
}

// create class to do repetitive string tests
class NginxStringConfigTest : public ::testing::Test {
protected:
    bool ParseString(const std::string& config_string) {
        std::stringstream config_stream(config_string);
        return parser_.Parse(&config_stream, &config_);
    };

    NginxConfigParser parser_;
    NginxConfig config_;
};

// test string that should pass
TEST_F(NginxStringConfigTest, SimpleTextConfig) {
    EXPECT_TRUE(ParseString("foo bar;"));
    // EXPECT_EQ("foo", config_.statements_[0]);
}

// test string without statement end
TEST_F(NginxStringConfigTest, SimpleBadTextConfig) {
    EXPECT_FALSE("foo bar");
}

// test nested configurations
TEST_F(NginxStringConfigTest, NestedConfig) {
    EXPECT_TRUE(
        ParseString(
            "http {"
            "  server {"
            "    listen 80;"
            "  }"
            "}"
        )
    );
}

// test a sample full Nginx config file
TEST(NginxConfigParserTest, FullConfig) {
  NginxConfigParser parser;
  NginxConfig out_config;

  bool success = parser.Parse("full_config_sample", &out_config);

  EXPECT_TRUE(success);
}
