function check()
  syscall_print("do check")
  return 0
end

function main(args)
  syscall_print("main1")
  contract["hello"]="world"
  syscall_print("main2")
  return 0
end

function init(args)
  syscall_print("init")
  contract = {}
  for i=1,#(args) do
	contract["arg"..i]=args[i]
  end
end
