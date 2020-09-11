Vagrant.configure("2") do |config|
  config.vm.box = "ubuntu/bionic64"

  config.vm.provider "virtualbox" do |vbox|
    # CPU、メモリなどは各自の環境で調整してください
    vbox.memory = (1024 * 4).to_s
    vbox.cpus   = 4
  end
  config.vm.network "forwarded_port", guest: 80, host: 8080
  config.vm.synced_folder ".", "/vagrant"
  # config.disksize.size = '20GB'
end
