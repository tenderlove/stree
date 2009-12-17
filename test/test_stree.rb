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
    assert_raises(TypeError) do
      @tree.push Object.new
    end
  end

  def test_push
    @tree.push 'foo'
  end

  def test_longest_common_substr
    @tree.push 'yokatta'
    @tree.push 'nemukatta'

    list = @tree.longest_common_substr(0, 10)
    assert_equal 'katta', list.first
  end
end
