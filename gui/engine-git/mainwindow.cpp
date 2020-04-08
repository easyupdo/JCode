#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->lineEdit->setEnabled(false);
  ui->lineEdit_2->setEnabled(false);
  ui->lineEdit_3->setEnabled(false);

  // ini
  QString app_dir = QCoreApplication::applicationDirPath();
  qDebug()<<app_dir;
  QSettings engine_set("/Users/jay/Personal/Study/QT/engine-test/engine-test/conf/engine.ini",QSettings::IniFormat);
  engine_set.setIniCodec(QTextCodec::codecForName("UTF-8"));
  this->engine_mode = engine_set.value("engine/engine_mode").toBool();
  this->engine_type = engine_set.value("engine/engine_type").toString();
  this->engine_ver = engine_set.value("engine/engine_ver").toString();
  this->engine_model = engine_set.value("engine/engine_model").toString();

  qDebug()<<this->engine_model;

  if(this->engine_mode) {
    ui->comboBox_3->setCurrentIndex(0);
    on_comboBox_3_activated(QString::fromLocal8Bit("批量题目测试"));
  } else {
    ui->comboBox_3->setCurrentIndex(1);
    on_comboBox_3_activated(QString::fromLocal8Bit("单个题目测试"));
  }

  ui->comboBox_2->setCurrentText(this->engine_type);
  ui->comboBox->setCurrentText(this->engine_ver);
  ui->lineEdit_3->setText(this->engine_model);

}

MainWindow::~MainWindow() {
  delete ui;
}

//选择测试模式
void MainWindow::on_comboBox_3_activated(const QString &arg1) {
  if(arg1 == "单个题目测试") {
    ui->pushButton_2->setText(QString::fromLocal8Bit("选择net目录"));
    ui->pushButton_3->setEnabled(true);
    this->engine_mode = false;
  } else {
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_2->setText(QString::fromLocal8Bit("选择list列表"));
    this->engine_mode = true;
  }

}

// engine_type
void MainWindow::on_comboBox_2_activated(const QString &arg1) {
  this->engine_type = arg1;
}

// engine_version
void MainWindow::on_comboBox_activated(const QString &arg1) {
  this->engine_ver = arg1;
}

//选择list列表
void MainWindow::on_pushButton_2_clicked() {
  this->file_lists.clear();
  engine_type = ui->comboBox_2->currentText();
  engine_ver = ui->comboBox->currentText();
  if (this->engine_mode) {
    // TODO list engine
    list_filename = QFileDialog::getOpenFileName();
    qDebug()<<list_filename<<engine_ver<<engine_type;
    QString appstr = "list"+list_filename+"\n"+"engine_type:"+engine_type+"\n"+"engine_version:"+engine_ver;
    ui->plainTextEdit->appendPlainText(appstr);
    ui->lineEdit->setText(list_filename);

  } else {
    // TODO one file
    net_dir = QFileDialog::getExistingDirectory();
    QDir dir(net_dir);
    QStringList filters = {"*.net"};
    QStringList file_lists_tmp = dir.entryList(filters);
    for(auto one : file_lists_tmp) {
      this->file_lists<<net_dir + "/" + one;
    }
    qDebug()<<file_lists;
    QString net;
    for(auto x : file_lists) {
      net += x +="  ";
    }
    QString appstr = "net_dir:"+net_dir+"\n"+"net:"+net;
    ui->plainTextEdit->appendPlainText(appstr);
    ui->lineEdit->setText(QString::fromLocal8Bit("共选择") + QString::number(file_lists.size()) + QString::fromLocal8Bit("文件"));
  }

}
// wav
void MainWindow::on_pushButton_3_clicked() {
  wav = QFileDialog::getOpenFileName();
  ui->lineEdit_2->setText(wav);
  ui->plainTextEdit->appendPlainText("waav:"+wav);
}

// Help
void MainWindow::on_pushButton_4_clicked() {
  Help help;
  help.exec();

}


// Stack-Trace:
// LOG

typedef std::string (*StackTraceHandle)();
void SetStackTraceHandle(StackTraceHandle handle);

/***** STACKTRACE *****/

static std::string Demangle(std::string trace_name) {
#if defined(HAVE_CXXABI_H) && defined(HAVE_EXECINFO_H)
  // at input the string looks like:
  //   ./kaldi-error-test(_ZN5kaldi13UnitTestErrorEv+0xb) [0x804965d]
  // We want to extract the name e.g. '_ZN5kaldi13UnitTestErrorEv",
  // demangle it and return it.

  // try to locate '(' and '+', take the string in between,
  size_t begin(trace_name.find("(")),
      end(trace_name.rfind("+"));
  if (begin != std::string::npos && end != std::string::npos && begin < end) {
    trace_name = trace_name.substr(begin + 1, end - (begin + 1));
  }
  // demangle,
  int status;
  char *demangled_name = abi::__cxa_demangle(trace_name.c_str(), 0, 0, &status);
  std::string ans;
  if (status == 0) {
    ans = demangled_name;
    free(demangled_name);
  } else {
    ans = trace_name;
  }
  // return,
  return ans;
#else
  return trace_name;
#endif
}


static std::string StackTrace() {
  std::string ans;
#ifdef HAVE_EXECINFO_H
#define KALDI_MAX_TRACE_SIZE 50
#define KALDI_MAX_TRACE_PRINT 20  // must be even.
  // buffer for the trace,
  void *trace[KALDI_MAX_TRACE_SIZE];
  // get the trace,
  size_t size = backtrace(trace, KALDI_MAX_TRACE_SIZE);
  // get the trace symbols,
  char **trace_symbol = backtrace_symbols(trace, size);

  // Compose the 'string',
  ans += "[ Stack-Trace: ]\n";
  if (size <= KALDI_MAX_TRACE_PRINT) {
    for (size_t i = 0; i < size; i++) {
      ans += Demangle(trace_symbol[i]) + "\n";
    }
  } else {  // print out first+last (e.g.) 5.
    for (size_t i = 0; i < KALDI_MAX_TRACE_PRINT / 2; i++) {
      ans += Demangle(trace_symbol[i]) + "\n";
    }
    ans += ".\n.\n.\n";
    for (size_t i = size - KALDI_MAX_TRACE_PRINT / 2; i < size; i++) {
      ans += Demangle(trace_symbol[i]) + "\n";
    }
    if (size == KALDI_MAX_TRACE_SIZE)
      ans += ".\n.\n.\n";  // stack was too long, probably a bug.
  }

  // cleanup,
  free(trace_symbol);  // it's okay, just the pointers, not the strings.
#endif  // HAVE_EXECINFO_H
  return ans;
}



StackTraceHandle GetStackTrace = StackTrace;




bool IsNetFile(std::string &in_file) {
  std::string file_name = in_file.substr(in_file.find_last_of(".") + 1);
  if (file_name == "net" || file_name == "NET")
    return true;
  else
    return false;
}

bool IsWavFile(std::string &in_file) {
  std::string file_name = in_file.substr(in_file.find_last_of(".") + 1);
  if (file_name == "wav" || file_name == "WAV")
    return true;
  else
    return false;
}


// 评测 file
void  MainWindow::Evaluation_File() {
  std::string ver = LsxAsesVersion();
  std::cout<<"Engine Version:"<<ver<<std::endl;
  auto time_start = std::chrono::system_clock::now();
  int err_code = 0;
  const char *polly_id = LsxAsesStart(this->engine_model.toStdString().c_str(), &err_code);
  qDebug()<<"Wavfile:LsxAsesStart:engine_id:"<<*polly_id;
  qDebug()<<"Wavfile:LsxAsesStart:err_code:"<<err_code;
  if (err_code)
    qDebug()<<QString::fromStdString(GetStackTrace());
  const char *session_id = LsxAsesSessionBegin(polly_id, this->engine_type.toStdString().c_str(), &err_code);
  qDebug()<<"Wavfile:LsxAsesSessionBegin:session_id:"<<*session_id;
  qDebug()<<"Wavfile:LsxAsesSessionBegin:err_code:"<<err_code;
  if (err_code)
    qDebug()<<QString::fromStdString(GetStackTrace());

  std::string wav_type = "wavfile";
  if (wav_type == "wavfile") {
    LsxAsesSessionSetParam(session_id, "md5", "1");
    for (auto one : this->file_lists) {
      err_code = LsxAsesSessionDataIn(session_id, one.toStdString().c_str(), 0, "netfile");
      qDebug()<<"Wavfile:LsxAsesSessionDataIn:err_code:"<<err_code;
      if (err_code)
        qDebug()<<QString::fromStdString(GetStackTrace());
    }
    err_code = LsxAsesSessionSpeechIn(session_id, this->wav.toStdString().c_str(), BUFFER_SIZE, "wavfile", NULL);
    qDebug()<<"Wavfile:LsxAsesSessionSpeechIn:err_code:"<<err_code;
    if (err_code)
      qDebug()<<QString::fromStdString(GetStackTrace());
  }
  if (wav_type == "wav") {
    char *flag = "1";
    char *name = "audio_quality";
    LsxAsesSessionSetParam(session_id, name, flag);

    char *vad_flag = "0";
    char *vad_name = "vad";
    LsxAsesSessionSetParam(session_id, name, flag);

    for (auto one : this->file_lists) {
      err_code = LsxAsesSessionDataIn(session_id, one.toStdString().c_str(), 0, "netfile");
    }
    FILE *fp = NULL;
    fp = fopen(this->wav.toStdString().c_str(), "rb");
    if (NULL == fp) {
    }
    fseek(fp, 0, SEEK_END);
    size_t wav_len = (ftell(fp) - 44);
    printf("######%d\n", wav_len);
    fseek(fp, 44, SEEK_SET);
    char *buffer = new char[wav_len];
    size_t nread = fread(buffer, sizeof(char), wav_len, fp);
    assert(nread == wav_len);
    fclose(fp);

    char ch_data[BUFFER_SIZE];
    int x = wav_len / BUFFER_SIZE;
    int y = wav_len % BUFFER_SIZE;
    char * ptr = buffer;
    for (int i = 0; i < x; i++) {
      memset(ch_data, 0, BUFFER_SIZE);
      memcpy(ch_data, ptr, BUFFER_SIZE);
      ptr += BUFFER_SIZE;
      err_code = LsxAsesSessionSpeechIn(session_id, ch_data, BUFFER_SIZE, "wav", NULL);
    }
    memset(ch_data, 0, BUFFER_SIZE);
    memcpy(ch_data, ptr, y);
    err_code = LsxAsesSessionSpeechIn(session_id, ch_data, y, "wav", NULL);
  }


  const char *result = LsxAsesSessionGetResult(session_id, "up366", NULL, &err_code);
  qDebug()<<"Engine:Mode:"<<this->engine_mode;
  qDebug()<<"Engine:Type:"<<this->engine_type;
  qDebug()<<"Engine:Version:"<<this->engine_ver;
  qDebug()<<"Engine:Model:"<<this->engine_model;

  for(auto net : this->file_lists)
    qDebug()<<"Engine:Net:"<<net;

  qDebug()<<"Engine:Wav:"<<this->wav;

  qDebug()<<"GetResult:LsxAsesSessionGetResult:result:"<<QString::fromLocal8Bit(result);
  qDebug()<<"GetResult:LsxAsesSessionGetResult:err_code:"<<err_code;
  if (err_code)
    qDebug()<<QString::fromStdString(GetStackTrace());

  printf("%s\n", result);
  err_code = LsxAsesSessionEnd(session_id);
  err_code = LsxAsesStop(polly_id);
  auto time_end = std::chrono::system_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(time_end - time_start);
  std::cout <<  "花费了"
            << double(duration.count()) * std::chrono::microseconds::period::num / std::chrono::microseconds::period::den
            << "秒" << std::endl;

  ui->plainTextEdit->appendPlainText("Engine Version:" + QString::fromStdString(ver));
  for(auto x : this->file_lists) {
    ui->plainTextEdit->appendPlainText(x);
  }
  ui->plainTextEdit->appendPlainText(this->wav);
  ui->plainTextEdit->appendPlainText(QString::fromLocal8Bit(result));
}

// 评测list
void  MainWindow::Evaluation_List() {
  // ### partc pass

#if OUTPUT
  /*
  std::string usage = "[exec X.lists model_dir outpt.txt]";
  if (argc != 4) {
  std::cout << "Usage:" << usage << std::endl;
  exit(1);
  }
   */
  std::string model_dir = this->engine_model.toStdString();
  //std::string lists = "/mnt/sdcard/Download/WorkDir/ZJ_partC-one-50-v2.1.txt";
  //std::string lists = "/mnt/sdcard/Download/WorkDir/测试矢量/partABC_list.txt";
  //std::string output = "/mnt/sdcard/Download/WorkDir/result/result_partc.txt";
  std::string output = "/mnt/sdcard/Download/WorkDir/result_partABC.txt";

  std::string lists ;
  std::string data_type ;
  std::string mession_type = this->engine_type.toStdString();


  /*
  //std::vector<std::string> mession = {"parta","partb","partc"};
  std::vector<std::string> mession = {"parta"};

  //######### parta partb partc

  for(auto mession_type:mession) {
   if (mession_type == "partc") {
     data_type = "path";
     lists = "/mnt/sdcard/Download/WorkDir/测试矢量/partC_list.txt";
   }
   if (mession_type == "parta") {
     data_type = "netfile";
     //lists = "/mnt/sdcard/Download/WorkDir/测试矢量/partA_list.txt";
     lists = "/mnt/sdcard/Download/WorkDir/iosou.txt";
   }
   if (mession_type == "partb") {
     data_type = "netfile";
     lists = "/mnt/sdcard/Download/WorkDir/测试矢量/partB_list.txt";
   }
  */


#else
  std::string usage = "[exec X.lists model_dir ]";
  if (argc != 3) {
    std::cout << "Usage:" << usage << std::endl;
    exit(1);
  }
#endif

  int err_code = 0;
  int user_session_count = 0;
  //const char *polly_id = PollyStart (argv[1], &err_code);
  const char *polly_id = LsxAsesStart(model_dir.c_str(), &err_code);

  std::string net_list_file = lists;

  std::ofstream ofs(output.c_str(), std::ios::app);
#if OUTPUT
  if (ofs.is_open()) {
#endif

    using NetList = std::vector<std::string>;
    std::string line;
    std::string file;
    std::ifstream in_stream;
    char buffer[1024];
    char ch[3];
    memset(buffer, 0, 1024);
#if DEBUG
    std::cout << "list_file:" << net_list_file << std::endl;
#endif
    in_stream.open(net_list_file);
    if (in_stream.is_open()) {
      bool newline = false;
      int session_num = 0;
      while (!in_stream.eof()) {
        const char *session_id = LsxAsesSessionBegin(polly_id, mession_type.c_str(),
                                 &err_code);
        user_session_count += 1;
        std::string wav;
        NetList net_list;
        getline(in_stream, line);
        if (line.size() <= 0)
          continue;
        newline = true;
        const char *cline = line.data();
        for (int i = 0; i < line.size(); i++) {
          if (cline[i] != ' ') {
            file = file + cline[i];
          } else {
            //file = "/home/liping/win10/300/"+ file;
            file = file;
            if (file.size() > 0) {
              if (IsNetFile(file))
                net_list.push_back(file);
              else if (IsWavFile(file))//wav
                if (net_list.size() == 0)
                  wav = file;
                else//others
                  net_list.push_back(file);
              file.clear();
            }
          }
        }
        //file = "/home/liping/win10/300/" + file;
        file = file;

        //if (IsNetFile(file))//if ䷾@蠾L纾S彝~_ if彘¯彍¢蠾L 佈¤彖­彘¯䷾M彘¯彖~G件
        if (IsWavFile(file)) {
          if (net_list.size() == 0)
            wav = file;
        } else
          net_list.push_back(file);
        file.clear();
#if DEBUG
        std::cout << "net_list:" << net_list.size()<<std::endl;
        std::cout << "Session num:" << ++session_num << std::endl;
        std::cout << "WAV:" << wav << " ";
        std::cout << "wav.c_str():" << wav.c_str() << std::endl;
#endif
#if OUTPUT
        ;
#else
        std::cout <<  wav << " ";
#endif
        auto time_start = std::chrono::system_clock::now();

        for (auto net : net_list) {
#if DEBUG
          std::cout << "Net:" << net << std::endl;
#endif
          //  ases_data.AsesDataIn(net.c_str(),0,"netfile");

          err_code = LsxAsesSessionDataIn(session_id, net.c_str(), 0,
                                          data_type.c_str());
        }
        FILE *fp = NULL;
        fp = fopen(wav.c_str(), "rb");
        if (NULL != fp) {
          fseek(fp, 0, SEEK_END);
          size_t wav_len = (ftell(fp) - 44);
          printf("######%d\n", wav_len);
          fseek(fp, 44, SEEK_SET);
          char *buffer = new char[wav_len];
          size_t nread = fread(buffer, sizeof(char), wav_len, fp);
          assert(nread == wav_len);
          fclose(fp);

          char ch_data[BUFFER_SIZE];
          int x = wav_len / BUFFER_SIZE;
          int y = wav_len % BUFFER_SIZE;
          char *ptr = buffer;
          for (int i = 0; i < x; i++) {
            memset(ch_data, 0, BUFFER_SIZE);
            memcpy(ch_data, ptr, BUFFER_SIZE);
            ptr += BUFFER_SIZE;
            err_code = LsxAsesSessionSpeechIn(session_id, ch_data, BUFFER_SIZE,
                                              "wav", NULL);
          }
          memset(ch_data, 0, BUFFER_SIZE);
          memcpy(ch_data, ptr, y);
          err_code = LsxAsesSessionSpeechIn(session_id, ch_data, y, "wav", NULL);


          int result_len = 0;
          const char *result = LsxAsesSessionGetResult(session_id, "up366",
                               &result_len, &err_code);

          //测试显示到屏幕
          //return env->NewStringUTF(result);

          auto time_end = std::chrono::system_clock::now();
          auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
                            time_end - time_start);
          double elapsed =
            double(duration.count()) * std::chrono::microseconds::period::num /
            std::chrono::microseconds::period::den;

#if DEBUG
          printf("%s\n", result);
#endif

          Document document;
          document.Parse(result);
          assert(document.HasMember("score"));
          assert(document["score"].IsDouble());
          double p_score = document["score"].GetDouble();
          //printf("%g %g\n", document["score"].GetDouble(),elapsed);

#if OUTPUT
          std::string pass_result = std::to_string(p_score);

          assert(document.HasMember("isReject"));
          assert(document["isReject"].IsInt());
          int p_isRegect = document["isReject"].GetInt();
          // printf("isRegect%d\n", document["isReject"].GetInt());
          std::string pass_Reject = std::to_string(p_isRegect);


          ofs.write("wav:", 4);
          ofs.write(wav.c_str(), wav.length());
          ofs.write("\t", 1);

          ofs.write("score:", 6);
          ofs.write(pass_result.c_str(), pass_result.length());
          ofs.write("\t", 1);

          ofs.write("IsRegect:", 9);
          ofs.write(pass_Reject.c_str(), pass_Reject.length());
          ofs.write("\t", 1);

          std::string user_session_count_str = std::to_string(user_session_count);
          ofs.write("count:", 5);
          ofs.write(user_session_count_str.c_str(), user_session_count_str.length());
          ofs.write("\t", 1);

          std::string srtime = std::to_string(elapsed);
          ofs.write("rtime:", 5);
          ofs.write(srtime.c_str(), srtime.length());
          ofs.write("\n", 1);

#endif
          ofs.flush();
          err_code = LsxAsesSessionEnd(session_id);
        } else
          std::cout << "wav open failed!" << std::endl;
      } //while
    } else {
      std::cout << "cannot open XXX.list" << std::endl;
    }
    in_stream.close();
#if OUTPUT
  } else
    std::cout << "output file open failed" << std::endl;
  ofs.close();
#endif
  err_code = LsxAsesStop(polly_id);

  /*
        //########### parta partb partc
      }
  */
}



// 开始测评
void MainWindow::on_pushButton_clicked() {
  if(this->engine_mode)
    Evaluation_List();
  else
    Evaluation_File();
}
// 选择模型
void MainWindow::on_pushButton_5_clicked() {
  this->engine_model = QFileDialog::getExistingDirectory();
  ui->lineEdit_3->setText(this->engine_model);
}



