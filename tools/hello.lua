function main(args)
  for k, v in pairs(args) do
    contract[k] = v;
  end
  return 0
end

