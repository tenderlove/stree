require "test/unit"
require "stree"

class Stree
  class TestString < Test::Unit::TestCase
    def test_bytesize
      str = "foo"
      assert_equal str.bytesize, Stree::String.new(str).bytesize
    end

    def test_square
      str  = "foo"
      sstr = Stree::String.new(str)

      0.upto(str.bytesize) do |i|
        if str.respond_to?(:getbyte)
          assert_equal str.getbyte(i), sstr[i], "failed on #{i}"
        else
          assert_equal str[i], sstr[i], "failed on #{i}"
        end
      end
    end
  end
end
