require "test/unit"
require "stree"

class Stree
  class TestStringSet < Test::Unit::TestCase
    def setup
      @ss = Stree::StringSet.new
    end

    def test_push_arg_error
      assert_raises(TypeError) do
        @ss << Object.new
      end
    end

    def test_push
      @ss << 'foo'
      assert_equal 1, @ss.length
    end

    def test_delete
      foo = 'foo'
      @ss << foo

      assert_equal 1, @ss.length
      assert_equal foo, @ss.delete(foo)
    end

    def test_delete_not_there
      foo = 'foo'
      assert_nil @ss.delete(foo)
    end

    def test_each
      foo = 'foo'
      @ss << foo
      list = []
      @ss.each do |thing|
        list << thing
      end

      assert_equal([foo], list)
    end
  end
end
