//rapidjson:github地址:https://github.com/Tencent/rapidjson

void CDecode::CDecodeIMPL::test()
{
	Document doc;
	StringBuffer buffer;
	doc.SetObject();
	Document::AllocatorType &allocator = doc.GetAllocator();
	doc.AddMember("A", "aaa", allocator);
	doc.AddMember("A", "aaa", allocator);
	doc.AddMember("A", "aaa", allocator);
	PrettyWriter<StringBuffer> pretty_writer(buffer);  //PrettyWriter是格式化的json，如果是Writer则是换行空格压缩后的json  
	doc.Accept(pretty_writer);
	//cout << "Buffer:" << buffer.GetString();
}