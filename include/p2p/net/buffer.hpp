#ifndef CC85AB15_2C9E_4D9A_82DA_735D16DEFBD4
#define CC85AB15_2C9E_4D9A_82DA_735D16DEFBD4


#include <vector>
#include <memory>

#include <boost/json.hpp>


namespace tinny
{
  namespace net
  {

	/*
	 トリビアル(Trivial)
	 → C++では, クラスや構造体は特殊メンバ関数を持つことができる. 
		- コンストラクタ = default
	 	- デストラクタ = default
	 	- コピーコンストラクタ = default
	 	- 代入演算子 = default
	 	- ムーブコンストラクタ = default
	
	これら全ての特殊メンバ関数が, 
	 - 全てdefault or implict されている
	 - ユーザ定義のバージョンが存在しない
	 - 仮想関数を持たない
	 - 非トリビアルなメンバ変数や基底クラスを持たない
	
	 つまり, メンバ変数のコピーや初期化, デストラクタ処理を特別に書かなくても単純なメモリコピー等(memcpy)で安全に処理ができる型
	 */

	
	// いかなるdataでもstd::vector< std::uint8_t > に変換する
	class buffer
	{
	  public:
		using value_type = std::uint8_t;
		using stream_type = std::vector< value_type >;
	  
	  private:
		std::vector<value_type> _data;
	  public:

		// trivially copyable な型に対するコンストラクタ
		template<typename T> requires std::is_trivially_copyable_v<T> buffer( const T& value )
		{
			/*
			std::is_trivially_copyable_v<T> : 型Tが単純なメモリコピ＝できる型か判定
			*/
			_data.resize( sizeof(T) ); // trivialだからsizeof(T)いけるってこと？
			std::memcpy( _data.data(), &value, sizeof(T) );
		}

		// std::string に対するコンストラクタ
		buffer( const std::string& str ) : 
			_data(str.begin(), str.end())
		{
			return;
		}

		// C言語の文字列(char*)に対するコンストラクタ
		buffer( const char* cstr )
		{
			if ( cstr )
			{
				std::size_t len = std::strlen(cstr);
				_data.resize(len);
				std::memcpy(_data.data(), cstr, len);
			}
			else
			{
				throw std::invalid_argument("Null pointer passed to buffer(const char*)");
			}
		}

		// 連続領域を持つコンテナに対するコンストラクタ
		template< typename Container >
		requires( // コンセプト機能(テンプレート引数に制約を課す) ()内がすべてtrueの際にテンプレートが有効化
			 std::is_same_v<typename Container::value_type, char> 
			 ||
			std::is_same_v<typename Container::value_type, value_type> 
		)
		buffer( const Container& container )
		{
			_data.resize( container.size() * sizeof(typename Container::value_type) );
			std::memcpy( _data.data(), container.data(), _data.size() );
		}
  
	  public:
		const std::vector<value_type>& data() const
		{
			return _data;
		}

		std::size_t size() const
		{
			return _data.size();
		}

		// virtual std::vector< value_type > serialize() const;
		// static std::unique_ptr<buffer> deserialize( std::vector<value_type>& data );
	};


  } // namespace net
} // namespace tinny


#endif 
