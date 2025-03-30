using TinnyControlLine = std::function<int(const std::vector<std::string>&)>;
  std::unordered_map< std::string, TinnyControlLine > cmdMap;

  boost::asio::io_context io_ctx;
  tinny_interface_client interface_client;

  cmdMap["ls"] = [interface_client]( TinnyControlLine ) -> int
  {
	std::cout << "ls" << "\n";

	if( args.size() > 2 )
	{
	  std::cout << "引数:"
	  for( int i=2; i < args.size(); ++i ) std::cout << " " << args[i];
	  std::cout << "\n";
	}
	return 0;
  }

  cmdMap["search"] = [interface_client]( TinnyControlLine ) -> int
  {
	std::cout << "search" << "\n";

	if( args.size() > 2 )
	{
	  std::cout << "引数:"
	  for( int i=2; i < args.size(); ++i ) std::cout << " " << args[i];
	  std::cout << "\n";
	}
	return 0;
  }
  cmdMap["download"] = [interface_client]( TinnyControlLine ) -> int
  {
	std::cout << "download" << "\n";

	if( args.size() > 2 )
	{
	  std::cout << "引数:"
	  for( int i=2; i < args.size(); ++i ) std::cout << " " << args[i];
	  std::cout << "\n";
	}
	return 0;
  }

  cmdMap["monitor"] = [interface_client]( TinnyControlLine ) -> int
  {
	std::cout << "monitor" << "\n";

	if( args.size() > 2 )
	{
	  std::cout << "引数:"
	  for( int i=2; i < args.size(); ++i ) std::cout << " " << args[i];
	  std::cout << "\n";
	}
	return 0;
  }


  std::string command = args[1]; // コマンドとして渡された文字列
  auto itr = cmdMap.find(command);
  if( itr != cmdMap.end() ) 
  {
	return itr->second(args);
  }
  else
  {
	std::cerr << "不明なコマンド" << command << "\n";
	return 1;
  }


