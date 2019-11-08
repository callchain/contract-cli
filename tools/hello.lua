function check()
  return 0
end

function main(args)
  contract["hello"]="world"
  return 0
end

function init(args)
  contract = {a="hello"}
end
  
