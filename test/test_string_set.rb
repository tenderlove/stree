require "test/unit"
require "stree"

class Stree
  class TestStringSet < Test::Unit::TestCase
    def setup
      @ss = Stree::StringSet.new
    end

    def test_push_arg_error
      assert_raises(ArgumentError) do
        @ss << Object.new
      end
    end

    def test_push
      @ss << Stree::String.new('foo')
      assert_equal 1, @ss.length
    end

    def test_delete
      foo = Stree::String.new('foo')
      @ss << foo

      assert_equal 1, @ss.length
      assert_equal foo, @ss.delete(foo)
    end

    def test_delete_not_there
      foo = Stree::String.new('foo')
      assert_nil @ss.delete(foo)
    end

    def test_delete_arg_error
      assert_raises(ArgumentError) do
        @ss.delete Object.new
      end
    end

    def test_each
      foo = Stree::String.new('foo')
      @ss << foo
      list = []
      @ss.each do |thing|
        list << thing
      end

      assert_equal([foo], list)
    end
  end
end
