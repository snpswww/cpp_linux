#include "gen-cpp/XSMBService.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <XSMBServiceHandler.h>
#include <infrastructure.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

using namespace  ::azure::storage::cpp_linux;

namespace azure {
	namespace storage {
		namespace cpp_linux 
		{
			// TODO: Add logging to these handler functions.

			void XSMBServiceHandler::PathExists(LinuxFileResponse& _return, const std::string& path) {
				printf("Calling [PathExists]\n");
				boost::filesystem::path b_path(path);
				try {
					if (boost::filesystem::exists(b_path)) {
						set_response(_return, true, path + " exists");
						std::cout << "[PathExists] - " << path << " exists." << std::endl;
					}
					else{
						set_response(_return, false, path + " does not exist");
						std::cout << "[PathExists] - " << path << " does not exist." << std::endl;
					}
				}
				catch (const std::exception& ex) {
					throw set_exception(ex.what(), OperationType::ListFile);
				}
			}

			void XSMBServiceHandler::CreateDirectory(LinuxFileResponse& _return, const std::string& dirPath) {
				printf("Calling [CreateDirectory]\n");		

				boost::filesystem::path dir(dirPath);
				try {
					if (boost::filesystem::exists(dir) && boost::filesystem::is_directory(dir)) {						
						set_response(_return, false, dirPath + ": directory already exists");						
						std::cout << "[CreateDirectory] - " << dirPath << ": directory already exists." << std::endl;
					}
					else {
						boost::filesystem::create_directory(dir);
						set_response(_return, true, "Successfully created directory " + dirPath);
						std::cout << "[CreateDirectory] - Successfully created directory " << dirPath << std::endl;
					}
				}
				catch (const std::exception& ex) {
					throw set_exception(ex.what(), OperationType::CreateDirectory);
				}
				return;
			}

			void XSMBServiceHandler::DeleteDirectory(LinuxFileResponse& _return, const std::string& dirPath, const bool isRecursive) {
				printf("Calling [DeleteDirectory]\n");
				
				boost::filesystem::path dir(dirPath);
				try {
					if (!boost::filesystem::exists(dir) || !boost::filesystem::is_directory(dir)) {						
						set_response(_return, false, dirPath + " does not exist or is not a directory");
						std::cout << "[DeleteDirectory] - " << dirPath << "does not exist or is not a directory" << std::endl;
					}
					else {
						if (boost::filesystem::is_empty(dir) || isRecursive) {							
							boost::filesystem::remove_all(dir);																					
							set_response(_return, true, "Successfully deleted directory " + dirPath);
							std::cout << "[DeleteDirectory] - Successfully deleted directory " << dirPath << std::endl;
						}
						else {							
							set_response(_return, false, dirPath + " is not empty while isRecursive is false");
							std::cout << "[DeleteDirectory] - " << dirPath << " is not empty while isRecursive is false" << std::endl;
						}
					}
				}
				catch (const std::exception& ex) {
					throw set_exception(ex.what(), OperationType::DeleteDirectory);
				}
				return;
			}

			void XSMBServiceHandler::CreateFile(LinuxFileResponse& _return, const std::string& filePath, const int64_t fileSize, const bool noBuffering) {
				printf("Calling [CreateFile]\n");
				
				boost::filesystem::path file(filePath);
				try {
					if (boost::filesystem::exists(file) && boost::filesystem::is_regular_file(file)) {				
						set_response(_return, false, filePath + " already exists");
						std::cout << "[CreateFile] - " << filePath << " already exists" << std::endl;
					}
					else {
						/*
						boost::filesystem::fstream fs;
						fs.open(file, boost::filesystem::fstream::out);
						fs.seekp(fileSize - 1);
						fs.write("", 1);
						fs.close();					
						*/
						int fd = creat(filePath.c_str(), 0777);
						boost::filesystem::resize_file(file, (uintmax_t)fileSize);
						close(fd);
						set_response(_return, true, "Successfully created " + filePath);
						std::cout << "[CreateFile] - Successfully created " << filePath << std::endl;
					}
				}
				catch (const std::exception& ex) {
					throw set_exception(ex.what(), OperationType::CreateFile);
				}
				return;
			}

			void XSMBServiceHandler::DeleteFile(LinuxFileResponse& _return, const std::string& filePath) {
				printf("Calling [DeleteFile]\n");
				
				boost::filesystem::path file(filePath);
				try {
					if (!boost::filesystem::exists(file) || !boost::filesystem::is_regular_file(file)) {
						set_response(_return, false, filePath + " does not exist or is not a file");
						std::cout << "[DeleteFile] - " << filePath << " does not exist or is not a file" << std::endl;
					}
					else {
						boost::filesystem::remove(file);
						set_response(_return, true, "Successfully deleted file " + filePath);
						std::cout << "[DeleteFile] - Successfully deleted file " << filePath << std::endl;
					}
				}
				catch (const std::exception& ex) {
					throw set_exception(ex.what(), OperationType::DeleteFile);
				}
				return;
			}

			void XSMBServiceHandler::ReadFile(LinuxFileResponse& _return, const std::string& filePath, const int64_t offset, const int64_t count) {
				printf("Calling [ReadFile]\n");

				boost::filesystem::path file(filePath);
				try {
					if (!boost::filesystem::exists(file) || !boost::filesystem::is_regular_file(file)) {
						set_response(_return, false, filePath + " does not exist or is not a file");
						std::cout << "[ReadFile] - " << filePath << " does not exist or is not a file" << std::endl;
					}
					else {
						std::fstream fs;
						fs.open(filePath.c_str(), std::ios::in);

						char* buffer = new char[count];

						fs.seekg(offset, fs.beg);

						fs.read(buffer, count);

						int64_t bytes_read = fs.gcount();

						std::string bytes_read_string = int_to_string(bytes_read);

						std::string buffer_string = std::string(buffer, bytes_read < count ? bytes_read : count);												

						fs.close();

						set_response(_return, true, "Successfully read from file " + filePath);
						std::cout << "[ReadFile] - Successfully read from file " << filePath << std::endl;
						std::map<std::string, std::string> additional_info;
						_return.__set_AdditionalInfo(additional_info);												
						_return.AdditionalInfo.insert(std::pair<std::string, std::string>("BytesRead", bytes_read_string));
						_return.__set_Buffer(buffer_string);
					}
				}
				catch (const std::exception& ex) {
					throw set_exception(ex.what(), OperationType::ReadFile);
				}
				return;
			}

			void XSMBServiceHandler::WriteFile(LinuxFileResponse& _return, const std::string& filePath, const int64_t offset, const std::string& buffer, const int64_t count) {
				printf("Calling [WriteFile]\n");
				boost::filesystem::path file(filePath);
				try {
					if (!boost::filesystem::exists(file) || !boost::filesystem::is_regular_file(file)) {
						set_response(_return, false, filePath + " does not exist or is not a file");
						std::cout << "[WriteFile] - " << filePath << " does not exist or is not a file" << std::endl;
					}
					else {
						std::fstream fs;
						fs.open(filePath.c_str());
						
						fs.seekp(offset);

						fs.write(buffer.c_str(), buffer.length());

						fs.close();

						set_response(_return, true, "Successfully write to " + filePath);
						std::cout << "[WriteFile] - Successfully write to " << filePath << std::endl;
					}
				}
				catch (const std::exception& ex) {
					throw set_exception(ex.what(), OperationType::WriteFile);
				}
				return;
			}

			boost::filesystem::recursive_directory_iterator create_recursive_directory_iterator(const boost::filesystem::path& path) {
				try {
					return boost::filesystem::recursive_directory_iterator(path);
				}
				catch (const boost::filesystem::filesystem_error& ex) {
					std::cout << ex.what() << std::endl;
					return boost::filesystem::recursive_directory_iterator();
				}
			}
			
			void dump(const boost::filesystem::path& path, int level) {
				try {
					std::cout << (boost::filesystem::is_directory(path) ? 'D' : ' ') << ' ';
					std::cout << (boost::filesystem::is_symlink(path) ? 'L' : ' ') << ' ';
					for (int i = 0; i < level; i++)
						std::cout << ' ';
					std::cout << level << ' ' << path.filename() << std::endl;
				}
				catch (const boost::filesystem::filesystem_error& ex) {
					std::cout << ex.what() << std::endl;
				}
			}

			void list_directory_recursive(const boost::filesystem::path& path, std::map<std::string, MatchInformation::type> & files, std::map<std::string, MatchInformation::type> & dirs) {
				//dump(path, 0);
				boost::filesystem::recursive_directory_iterator it = create_recursive_directory_iterator(path);
				boost::filesystem::recursive_directory_iterator end;
				while (it != end) {					
					/* Take care of symbolic link later.
					if (boost::filesystem::is_directory(*it) && boost::filesystem::is_symlink(*it))
						it.no_push();
					*/					
					try {
						dump(*it, it.level());
						if (boost::filesystem::is_directory(*it))
							dirs.insert(std::pair<std::string, MatchInformation::type>(boost::filesystem::path(*it).string(), MatchInformation::OnlyOnServer));
						else if (boost::filesystem::is_regular_file(*it))
							files.insert(std::pair<std::string, MatchInformation::type>(boost::filesystem::path(*it).string(), MatchInformation::OnlyOnServer));
						it++;						
					}
					catch (const boost::filesystem::filesystem_error& ex) {
						std::cout << ex.what() << std::endl;
						it.no_push();
						try {
							it++;
						}
						catch (...) {
							std::cout << "!!" << std::endl;
						}
					}
				}
			}

			void XSMBServiceHandler::ListFiles(LinuxFileResponse& _return, const std::string& dirPath, const bool isRecursive) {
				printf("Calling [ListCloudFiles]\n");
				boost::filesystem::path dir(dirPath);
				std::map<std::string, MatchInformation::type> files, dirs;
				try {
					list_directory_recursive(dir, files, dirs);
					set_response(_return, true, "Success");
					_return.__set_Directories(dirs);
					_return.__set_Files(files);
				}
				catch (const boost::filesystem::filesystem_error& ex) {
					std::cout << ex.what() << std::endl;
				}
				return;
			}

			void XSMBServiceHandler::GetFileLength(LinuxFileResponse& _return, const std::string& filePath) {
				printf("Calling [GetFileLength]\n");
				boost::filesystem::path file(filePath);				
				try {
					if (boost::filesystem::exists(file) && boost::filesystem::is_regular_file(file)) {			
						set_response(_return, true, "Successfully get file length for " + filePath);
						std::cout << "[GetFileLength] - Successfully get file length for " << filePath << std::endl;
						
						int64_t file_size =  (int64_t)boost::filesystem::file_size(file);
						std::string file_size_string = int_to_string(file_size);

						std::map<std::string, std::string> additional_info;
						_return.__set_AdditionalInfo(additional_info);
						_return.AdditionalInfo.insert(std::pair<std::string, std::string>("FileLength", file_size_string));						
					}
					else {
						set_response(_return, false, filePath + " does not exist or is not a file");
						std::cout << "[GetFileLength] - " << filePath << " does not exist or is not a file" << std::endl;
					}
				}
				catch (const std::exception& ex) {
					throw set_exception(ex.what(), OperationType::GetFileLength);
				}				
				return;
			}

			void XSMBServiceHandler::SetFileLength(LinuxFileResponse& _return, const std::string& filePath, const int64_t fileLength) {
				printf("SetCloudFileLength\n");				
				boost::filesystem::path file(filePath);
				try {
					if (boost::filesystem::exists(file) && boost::filesystem::is_regular_file(file)) {						
						boost::filesystem::resize_file(file, (uintmax_t)fileLength);
						set_response(_return, true, "Successfully set file length!");
					}
					else {
						set_response(_return, false, filePath + " does not exist or is not a file");
					}
				}
				catch (const std::exception& ex) {
					throw set_exception(ex.what(), OperationType::SetFileLength);
				}
				return;
			}

			void XSMBServiceHandler::OpenFileHandle(LinuxFileResponse& _return, const std::string& filePath, const LinuxFileMode::type fileMode, const LinuxFileAccess::type fileAccess, const int32_t handleId) {
				std::cout << "OpenFileHandle" << std::endl;
				boost::filesystem::path file(filePath);
				try {	
					/*
					 * Linux System Call
					 */
					int flag = set_file_flag(fileAccess, fileMode);
					int fd = open(filePath.c_str(), flag);
					if (fd == -1) {
						printf("open() failed with error[%s]\n", strerror(errno));
						set_response(_return, false, "open() failed with error [" + std::string(strerror(errno)) + "]");
						return;
					}
					FILE* file = fdopen(fd, "rb+");
					file_pointers.insert(std::pair<int, FILE*>(fd, file));
					std::cout << "#handles: " << file_pointers.size() << std::endl;
					set_response(_return, true, "Sucessfully opened file handler [" + int_to_string(fd) + "]");

					std::map<std::string, std::string> additional_info;
					_return.__set_AdditionalInfo(additional_info);
					_return.AdditionalInfo.insert(std::pair<std::string, std::string>("FileDescriptor", int_to_string(fd)));
				}
				catch (const std::exception& ex) {
					throw set_exception(ex.what(), OperationType::WriteFile);
				}
				return;
			}

			void XSMBServiceHandler::CloseFileHandle(LinuxFileResponse& _return, const int32_t handleId) {				
				std::cout << "CloseFileHandle" << std::endl;
				try {
					std::map<int, FILE*>::iterator it = file_pointers.find(handleId);
					if (it != file_pointers.end()) {
						FILE* file = it->second;
						fclose(file);
						file_pointers.erase(it);
						close(it->first);						
						std::cout << "Successfully closed file handle [" << handleId << "]" << std::endl;
						set_response(_return, true, "Successfully closed file handle [" + int_to_string(handleId) + "]");
					}
					else {
						std::cout << "File handle [" << handleId << "] does not exist. It may have been closed." << std::endl;
						set_response(_return, false, "File handle [" + int_to_string(handleId) + "] does not exist. It may have been closed.");
					}
				}
				catch (const std::exception& ex) {
					throw set_exception(ex.what(), OperationType::WriteFile);
				}
				return;
			}

			void XSMBServiceHandler::ReadFileByHandle(LinuxFileResponse& _return, const int32_t handleId, const int64_t offset, const int64_t count) {
				std::cout << "ReadFileByHandle" << std::endl;
				try {
					std::map<int, FILE*>::iterator it = file_pointers.find(handleId);
					if (it != file_pointers.end() && it->second != NULL) {
						FILE* file = it->second;
						char* buffer = new char[count];
						fseek(file, offset, SEEK_SET);
						int64_t bytes_read = fread(buffer, sizeof(char), count, file);

						std::string bytes_read_string = int_to_string(bytes_read);
						std::string buffer_string = std::string(buffer, bytes_read < count ? bytes_read : count);
						std::cout << "bytes_read: [" << bytes_read_string << "]" << std::endl;
						std::cout << "buffer_string: [" << buffer_string << "]" << std::endl;
						std::cout << "buffer_string.length(): [" << buffer_string.length() << "]" << std::endl;
						set_response(_return, true, "Successfully read from file handle [" + int_to_string(handleId) + "]");

						std::map<std::string, std::string> additional_info;
						_return.__set_AdditionalInfo(additional_info);
						_return.AdditionalInfo.insert(std::pair<std::string, std::string>("BytesRead", bytes_read_string));
						_return.__set_Buffer(buffer_string);
					}
					else {
						std::cout << "file handle [" << handleId << "] does not exist, or somehow it has been closed." << std::endl;
						set_response(_return, false, "file handle [" + int_to_string(handleId) + "] does not exist, or somehow it has been closed.");
					}
				}
				catch (const std::exception& ex) {
					throw set_exception(ex.what(), OperationType::WriteFile);
				}
				return;
			}

			void XSMBServiceHandler::WriteFileByHandle(LinuxFileResponse& _return, const int32_t handleId, const int64_t offset, const std::string& buffer, const int64_t count) {
				std::cout << "WriteFileByHandle" << std::endl;
				try {								
					std::map<int, FILE*>::iterator it = file_pointers.find(handleId);
					if (it != file_pointers.end() && it->second != NULL) {
						std::cout << "Start writing..." << std::endl;
						FILE* file = it->second;
						fseek(file, offset, SEEK_SET);
						fwrite(buffer.c_str(), sizeof(char), buffer.length(), file);
						fflush(file);
						std::cout << "Should write: [" << buffer << "]" << std::endl;
						set_response(_return, true, "Successfully write to file handle [" + int_to_string(handleId) + "]");
					}
					else {
						std::cout << "file handle [" << handleId << "] does not exist, or somehow it has been closed." << std::endl;
						set_response(_return, false, "file handle [" + int_to_string(handleId) + "] does not exist, or somehow it has been closed.");
					}
				}
				catch (const std::exception& ex) {
					throw set_exception(ex.what(), OperationType::WriteFile);
				}
				return;
			}

			void XSMBServiceHandler::CopyFile(LinuxFileResponse& _return, const std::string& sourcePath, const std::string& destinationPath, const bool overwriteIfExists) {
				std::cout << "Calling [CopyFile]" << std::endl;
				boost::filesystem::path source(sourcePath), destination(destinationPath);
				try {
					if (!overwriteIfExists && boost::filesystem::exists(destination)) {
						set_response(_return, false, destinationPath + " exists, copy failed.");
						std::cout << destinationPath << " exists, copy failed." << std::endl;
					}
					else {
						/*
						boost::filesystem::copy_file(source, destination, boost::filesystem::copy_option::overwrite_if_exists);
						*/
						std::string cmd = "cp ";
						if (overwriteIfExists)
							cmd += "-f ";
						else
							cmd += "-n ";
						cmd += sourcePath + " " + destinationPath;
						exec(cmd.c_str());
						std::cout << "[CopyFile] - Running command - " << cmd << std::endl;
						set_response(_return, true, "Succesfully copied " + sourcePath + " to" + destinationPath);
						std::cout << "[CopyFile] - Source - " << sourcePath << " - Destination - " << destinationPath << std::endl;
					}				
				} 
				catch (const std::exception& ex) {
					throw set_exception(ex.what(), OperationType::CreateDirectory);
				}
				return;
			}

			void XSMBServiceHandler::MoveFile(LinuxFileResponse& _return, const std::string& sourcePath, const std::string& destinationPath, const bool overwriteIfExists, const bool fileCopyAllowed) {
				std::cout << "Calling [MoveFile]" << std::endl;
				boost::filesystem::path source(sourcePath), destination(destinationPath);
				try {
					if (fileCopyAllowed) {
						if (!overwriteIfExists && boost::filesystem::exists(destination)) {
							set_response(_return, false, "overwriteIfExists: " + (overwriteIfExists ? std::string("[true]. ") : std::string("[false]. ")) +  destinationPath + " exists, move failed.");
							std::cout << "[MoveFile] - overwriteIfExists: " << (overwriteIfExists ? "[true] - " : "[false] - ") << destinationPath << " exists, move failed." << std::endl;
						}
						else {
							//boost::filesystem::copy_file(source, destination);
							std::string cp_cmd = "cp ";
							cp_cmd += "-f " + sourcePath + " " + destinationPath;
							exec(cp_cmd.c_str());
							boost::filesystem::remove(source);
							set_response(_return, true, "Successfully moved " + sourcePath + " to " + destinationPath);
							std::cout << "[MoveFile] - Successfully moved " << sourcePath << " to " << destinationPath << std::endl;
						}
					} 
					else {
						std::string cmd = "mv ";
						if (overwriteIfExists)
							cmd += "-f ";
						else
							cmd += "-n ";
						cmd += sourcePath + " " + destinationPath;
						exec(cmd.c_str());
						std::cout << "[MoveFile] - Running command - " << cmd << std::endl;
						set_response(_return, true, "Successfully moved " + sourcePath + " to " + destinationPath);
						std::cout << "[MoveFile] - Successfully moved " << sourcePath << " to " << destinationPath << std::endl;
					}
				}
				catch (const std::exception& ex) {
					throw set_exception(ex.what(), OperationType::CreateDirectory);
				}
				return;
			}

			void XSMBServiceHandler::TruncateFile(LinuxFileResponse& _return, const std::string& filePath) {
				std::cout << "Calling [TruncateFile]" << std::endl;
				boost::filesystem::path file(filePath);
				try {
					if (!boost::filesystem::exists(file) || !boost::filesystem::is_regular_file(file)) {
						set_response(_return, false, filePath + " does not exist or is not a file");
						std::cout << "[TruncateFile] - " << filePath << " does not exist or is not a file" << std::endl;
					}
					else {
						boost::filesystem::fstream fs;
						fs.open(file, boost::filesystem::fstream::out);						
						fs.close();
						set_response(_return, true, "Successfully truncated " + filePath);
						std::cout << "[TruncateFile] - Successfully truncated " << filePath << std::endl;
					}
				}
				catch (const std::exception& ex) {
					throw set_exception(ex.what(), OperationType::CreateDirectory);
				}
				return;
			}


		}
	}
}
