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

      if str.respond_to?(:getbyte)
        0.upto(str.bytesize) do |i|
          assert_equal str.getbyte(i), sstr[i], "failed on #{i}"
        end
      else
        0.upto(str.bytesize) do |i|
          assert_equal str[i], sstr[i], "failed on #{i}"
        end
      end
    end
  end
end
