#include <interface/client.hpp>
#include <core/core.hpp>

#include <iostream>
#include <string>
#include <cstdio>
#include <vector>
#include <unordered_map>
#include <functional>

#include <boost/asio.hpp>
#include <boost/asio/local/stream_protocol.hpp>


int main( int argc, const char *argv[] )
{
  std::vector< std::string > args(argv, argv + argc);

  
  // Tinnyを起動する : デーモン起動するべき(systemd)
  if( args.size() == 1 )
  {
	// ::unlink( tinny::interface::SOCKET_PATH.c_str() ); // 指定したファイルへのリンク(参照)を削除する
	

	boost::asio::io_context io_ctx;
	tinny::core core(io_ctx);
	core.start();


	auto work_gurad = boost::asio::make_work_guard(io_ctx);

	std::cout << "Tinny起動: " << tinny::interface::SOCKET_PATH << " で待機中..." << "\n";

	io_ctx.run(); // 非同期処理ループ開始
	return 0;
  }


  if( args.size() >= 2 )
  {
	io_context io_ctx;
	tinny::interface::cui_client clinet( io_ctx );

	std::string command = "ls";
	std::string count = "あああ";
	std::vector< std::string > tokens = {command, count};

	std::cout << "送信コマンド : ";
	for( const auto& i : tokens )
	{
	  std::cout << i << "\n";
	}

	clinet.send( tokens );
	io_ctx.run();

	return 0;
  }

  
  std::cout << "Hello World" << "\n";
}
