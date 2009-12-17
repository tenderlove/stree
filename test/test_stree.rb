require "test/unit"
require "stree"

class TestStree < Test::Unit::TestCase
  def setup
    @tree = Stree.new
  end

  def test_new
    assert Stree.new
  end

  def test_push_argerror
    assert_raises(ArgumentError) do
      @tree.push Object.new
    end
  end

  def test_push
    @tree.push Stree::String.new('foo')
  end

  def test_longest_common_substr
    @tree.push Stree::String.new('yokatta')
    @tree.push Stree::String.new('nemukatta')

    list = @tree.longest_common_substr(0, 10)
    assert_equal 'katta', list.first.to_s
  end
end
