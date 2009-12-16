require "test/unit"
require "stree"

class TestStree < Test::Unit::TestCase
  def test_new
    assert Stree.new
  end
end
