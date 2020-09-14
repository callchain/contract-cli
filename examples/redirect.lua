-- entry
-- redirect received amount to `to` address
function main(args)
  ret, err = syscall_transfer(args.to, msg.value)
  return err
end

