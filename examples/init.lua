-- entry
function main(args)
  contract["hello"]="world"
  return 0
end

-- init contract parameters
function init(args)
  contract = {}
  for i=1,#(args) do
	contract["arg"..i]=args[i]
  end
end
