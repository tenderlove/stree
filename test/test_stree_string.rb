require 'stree'
require 'test/unit'

module STree
  class TestString < Test::Unit::TestCase
    def test_length
      string = STree::String.new 'foo'
      assert_equal 3, string.length
    end

    def test_type_error
      assert_raises(TypeError) do
        STree::String.new Object.new
      end
    end
  end
end
