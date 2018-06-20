#ifndef VERIFY_H
#define VERIFY_H

#include "md5.h"

namespace n_verify
{
    class CVerify
    {
    public:
        CVerify(){}

        //将str写到filename的文件
        void Write(std::string str,std::string filename)
        {
            std::ofstream ofs(filename,std::ios::app);
            if(ofs.is_open())
            {
                ofs.write(str.data(),str.length());
                ofs.write("\n",1);
                ofs.close();
            }
        }

        /**
            * @brief  生成每一个数据包的MD5序列保存在私有变量package_md5结构中
            * @param  参数1:string text:每一个数据包的string
            *
            * @return void
            */
        void SetPackageMD5(std::string text)
        {
            this->md5.update(text.c_str(), text.length());
            this->md5.Set_finalized_Inti_Status();
            this->md5.finalize();
            std::string md5_str =  this->md5.md5();
            package_md5.push_back(md5_str);
           // qDebug()<<"md5_str:"<<md5_str;
        }
        //返回存储每一个数据包的MD5结构
        std::vector<std::string> GetallPackageMD5()
        {
            return package_md5;
        }

        /**
            * @brief  从私有变量package_md5结构中读取每一个数据包的MD5序列后生成总的MD5序列
            * @param  参数1:std::vector<std::string> &vec:存储每一个数据包的MD5序列
            * @param  参数1:std::string filename:保存生成的md5的文件名
            * @return void
            */
        void SetTXTMD5(std::vector<std::string> &vec,std::string filename)
        {
            std::string str;

            std::ofstream file(filename);
            if (file.is_open())
            {
                file.close();
                remove(filename.c_str());
            }//clean the file

            std::ofstream ofs(filename,std::ios::app);
            if(ofs.is_open())
            {
                std::vector<std::string>::iterator it = vec.begin();
                std::string package = "MD5 for each packet:";
                ofs.write(package.data(),package.length());
                ofs.write("\n",1);
                for(;it != vec.end();it++)
                {
                    ofs.write((*it).data(),(*it).length());
                    ofs.write("\n",1);
                    str = str + (*it) ;
                }
                this->md5.update(str.c_str(), str.length());
                this->md5.Set_finalized_Inti_Status();
                this->md5.finalize();
                std::string md5_str =  this->md5.md5();
                std::string txt = "MD5 generated using the MD5 sum of each packet:";
                ofs.write(txt.data(),txt.length());
                ofs.write("\n",1);
                ofs.write(md5_str.data(),md5_str.length());
                ofs.write("\n",1);

                ofs.close();
             }
        }

    private:
        std::vector<std::string>package_md5;//存储每一个数据包的MD5序列
        MD5 md5;//MD5计算类


    };
}
#endif // VERIFY_H
