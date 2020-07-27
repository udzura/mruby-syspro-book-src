class Target
  def initialize(path)
    @path = path
  end

  def get_size
    f = File.open(@path, 'r')
    content = f.read
    f.close
    return content.size
  end

  def get_line
    f = File.open(@path, 'r')
    content = f.read
    f.close
    return content.split("\n").size
  end

  def self.passwd_instance
    self.new "/etc/passwd"
  end

  def self.shadow_instance
    self.new "/etc/shadow"
  end
end

tgt = Target.passwd_instance
printf "Size is %d\n", tgt.get_size
printf "Line is %d\n", tgt.get_line
