class Stree
  class StringSet
    def initialize
      @weak_refs = {}
    end

    alias :<< :push
  end
end
