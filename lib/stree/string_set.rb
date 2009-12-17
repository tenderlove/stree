class Stree
  class StringSet
    include Enumerable

    def initialize
      @weak_refs = {}
    end

    alias :<< :push
  end
end
