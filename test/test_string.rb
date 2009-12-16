require "test/unit"
require "stree"

class Stree
  class TestString < Test::Unit::TestCase
    def test_bytesize
      str = "foo"
      assert_equal str.bytesize, Stree::String.new(str).bytesize
    end
  end
end
