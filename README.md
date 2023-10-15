# minishell
This is work space of "minishll" (one of 42cursus project).

# to think.
・ check all function's document.  
・ read minishell repo.  
・ understand about "lexer" & "parser".  

# to do
・ 閉じられていない引用符や、指定されていない特殊文字（\ や ;）を解釈する必要はない  
・ 1つ以上のグローバル変数を使用してはいけません。また、そうする理由を考えて、説明する準備をしてください  
・ コマンドの入力を待機する際、プロンプト(訳者註: 入力開始位置を示す文字)を表示してください  
・ working histroy(訳者註: 実行したコマンドの履歴)を保持してください  
・ PATH変数および相対パス/絶対パスを用いて入力されたコマンドの正しい実行ファイルを探し出し、起動してください  
・ 以下のビルトインコマンドを実装してください  
	*echo （-n オプションの挙動を含む）  
 	*cd　（相対パス、または絶対パスのみで動作する）  
 	*pwd　（オプションの処理を含まない）  
   	*export　（オプションの処理を含まない）  
   	*unset　（オプションの処理を含まない）  
   	*env　（オプションと引数の処理を含まない）  
   	*exit　（オプションの処理を含まない）  
・ 「'」は、すべてのシーケンス文字の解釈を抑制します  
・ 「"」 は、「$」をのぞくすべてのシーケンス文字の解釈を抑制します  
・ リダイレクト  
	*「<」で、入力のリダイレクトを行ってください  
 	*「>」で、出力のリダイレクトを行ってください  
 	*「<<」では、現在の入力元から区切り文字列だけを含む行が現れるまで読み込みます。履歴の更新は必要ありません！  
	*「>>」は、出力のリダイレクトを追記モードで行ってください  
・ パイプ「|」は、パイプラインの各コマンドの出力結果を、パイプを通して次のコマンドの入力につなげます  
・ 環境変数（「$」に続く文字列）は、その値に展開してください  
・ 「$?」は、直近にフォアグラウンドで実行されたパイプラインのコマンドの終了ステータスを展開してください  
・ 「ctrl-C」、「ctrl-D」、そして「ctrl-\」は、bashの場合と同じ結果となるようにしてください  
・ インタラクティブのとき（訳者註: コマンド入力待ちの状態で）：  
	*Ctrl - C : 次の行に、プロンプトを表示してください  
	*Ctrl - D : シェルを終了してください✅  
	*Ctrl - \ : 何も行わないでください  

# function memo
 readline  
 `char *readline (char *prompt);` `prompt`で指定された文字を行頭に表示しつつ、返り値に読み取った行を返す。返り値に'\n'は含まれない。　空白行は空白の文字列を返す。行の読み取り中にEOFが検出され、その行が空の時、NULLを返す。EOFが検出されたが、その行が空でない場合、EOFは改行として扱われる。  
 rl_clear_history  
 `void rl_clear_history (void);` readlineの履歴を削除する。  
 rl_on_new_line  
 `int	rl_on_new_line(void);` ラインを更新して再表示する。  
 rl_replace_line  
 `void rl_replace_line (const char *text, int clear_undo);`  。  
 rl_redisplay  
 `void rl_redisplay (void);` 。  
 add_history  
 `int	add_history(const char *);`。  
 
 printf  
 malloc  
 free  
 write  
 access  
 open  
 read  
 close  
 fork  
 wait  
 waitpid  
 wait3  
 wait4  
 signal  
 sigaction  
 sigemptyset  
 sigaddset  
 kill  
 exit  
 execve  
 dup  
 dup2  
 pipe  
   
 getcwd  
 `char *getcwd(char *buf, size_t length);`現在のディレクトリ名を取得し、`buf`に入れる。  
 chdir  
 `int *chdir(const char *path)` `path`で指定され文字列にカレントディレクトリに変更する。  
 stat  
 `int stat(const char *pathname, struct stat *buf);` ファイルやディレクトリの状態を取得する `path`で状態を取得したいもののパス名を指定する。 `buf`は、取得した状態を格納するstat構造体を指定する。  
 lstat  
 `int lstat(const char *path, struct stat *sb);` stat関数とほぼ同じ。違うのは、指定したファイルがシンボリックリンクだった時に、stat()はリンクの情報を、lstat()はリンクが参照するファイルの情報を返す。  
 fstat  
 `int fstat(int fd, struct stat *sb);` stat()がcharのpathで指定するのに対し、fstat()はファイルディスクリプた`fd`で指定する。`sb`に格納する値は同じ。  
 unlink  
 `int unlink(const char *pathname);` ファイルシステム上の名前を削除する。もし、その指定した名前がファイルへの最後のlinkで、どのプロセスでもopen()されていなければ、ファイルは削除される。  
 
 opendir  
 `DIR *opendir(const char *name);` ディレクトリを開く。`name`で指定したディレクトリをオープンし、ディレクトリストリームを返す。  
 readdir  
 `struct dirent *readdir(DIR *dirp);` `dirp`で指定するディレクトリストリームの中で、次のディレクトリエントリーについての`dirent`構造体へのポインターを返す。  
 closedir  
 `int closedir(DIR *dirp);` `dirp`で指定したディレクトリストリームをcloseする。成功は0、エラーは-1を返す。エラーはerrnoを設定する。  
 strerror  
 `また後で` `errno`を渡すと、対応する文字列を返す。  
 perror  
 `また後で` `errno`を渡すと、対応する文字列を出力する。  
 isatty  
 `int isatty(int fd);` `fd`が端末を参照するファイルディスクリプタかどうかを判定する。そうであれば1、違えば0を返し、errnoを設定する。  
 ttyname  
 `char *ttyname(int fd);`ttyの端末名を取得する  
 ttyslot  
 `int ttyslot(void);` ttyスロット番号(?)を整数値で返す。  
 ioctl  
 `int ioctl(int fd, unsigned long request, ...);` ちょっと説明がむずすぎて訳わかんなかった。  
 getenv  
 `char *getenv(const char *name);` `name`で指定した名前の環境変数の値を返す。  
 tcsetattr  
 `int tcsetattr(int fd, int when, const struct termios *termptr);`termios構造体を設定する。tcgetattr()するための準備?のような感じ。  
 tcgetattr  
 `int tcgetattr(int fildes, struct termios *termptr);`端末(tty)の設定を取得する関数。ttyデバイスの特定の設定に関する情報を取得するために使用する。  
 tgetent  
 `int tgetent(char *bp, const char *name);` 端末(tty)のキャパビリティデータベースを読み込むための関数。  
 tgetflag  
 `int tgetflag(const char *id);` 端末(tty)のキャパビリティデータベースからフラグ(boolean値)を取得するための関数。  
 tgetnum  
 `int tgetnum(const char *id);` 端末(tty)のキャパビリティデータベースから数値キャパビリティを取得するための関数。  
 tgetstr  
 `char *tgetstr(const char *id, char **area);` 端末(tyy)のキャパビリティデータベースからエスケープシーケンスを取得するための関数。  
 tgoto  
 `char *tgoto(const char *cap, int col, int row);` 端末(tty)に依存するエスケープシーケンス内のパラメータを置き換えるための関数。  
 tputs  
 `int tputs(const char *str, int affcnt, int (*putfunc)(int));` 端末(tty)にエスケープシーケンスを送信するための関数。


 
