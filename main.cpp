#include <fstream>
#include <iostream>
#include <memory>

#include <openssl/evp.h>

#include <message_generated.h>

//TODO: some error checking in the (de|en)cryption code
//TODO: the key and initial vector should be hidden somehow
int aes_encode(const uint8_t *data, size_t data_len, std::unique_ptr<uint8_t[]> &data_out)
{
	EVP_CIPHER_CTX *ctx;
	unsigned char key[32] = "ScherzIndustries";
	unsigned char iv[16] = "012345678901234";

	// memory at least 2 blocksizes bigger than input
	std::unique_ptr<uint8_t[]> encrypted(new uint8_t[16 * ((data_len + 15) / 16 + 2)]);

	int outlen1, outlen2;

	ctx = EVP_CIPHER_CTX_new();
	EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, key, iv);
	EVP_EncryptUpdate(ctx, encrypted.get(), &outlen1, data, data_len);
	EVP_EncryptFinal_ex(ctx, encrypted.get() + outlen1, &outlen2);

	EVP_CIPHER_CTX_free(ctx);

	data_out = std::move(encrypted);

	return outlen1 + outlen2;
}

int aes_decode(const uint8_t *data, size_t data_len, std::unique_ptr<uint8_t[]> &data_out)
{
	EVP_CIPHER_CTX *ctx;
	unsigned char key[32] = "ScherzIndustries";
	unsigned char iv[16] = "012345678901234";

	std::unique_ptr<uint8_t[]> decrypted(new uint8_t[data_len]);

	int outlen1, outlen2;

	ctx = EVP_CIPHER_CTX_new();
	EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, key, iv);
	EVP_DecryptUpdate(ctx, decrypted.get(), &outlen1, data, data_len);
	EVP_DecryptFinal_ex(ctx, decrypted.get() + outlen1, &outlen2);

	EVP_CIPHER_CTX_free(ctx);

	data_out = std::move(decrypted);

	return outlen1 + outlen2;
}

void step1_write()
{
	std::srand(234);
	MyMessage::MessageT message;
	message.id=1;
	message.name="Woooooooow";
	message.content="Something contenty!";
	message.bindata.reserve(1000);

	for (size_t i = 0; i < 1000; ++i)
	{
		message.bindata.push_back((uint8_t)std::rand());
	}

	std::cout << "\n## Encode"
		<< "\nid: " << message.id
		<< "\nName: " << message.name
		<< "\nContent: '" << message.content << "'\n"
		<< message.bindata[0] + message.bindata[1] + message.bindata[3]
		<< std::endl;

	flatbuffers::FlatBufferBuilder builder;
	builder.Finish(MyMessage::Message::Pack(builder, &message));

	std::ofstream out;
	out.open("encoded_message.bin", std::ios::binary | std::ios::out);

	std::unique_ptr<uint8_t[]> data_out(nullptr);
	int data_out_len = aes_encode(
			builder.GetBufferPointer(),
			builder.GetSize(),
			data_out);

	out.write((char*)data_out.get(), data_out_len);

	out.close();
}

void step2_read()
{
	std::ifstream in;
	in.open("encoded_message.bin", std::ios::binary | std::ios::in);
	in.seekg(0, std::ios::end);
	size_t data_len = in.tellg();

	std::unique_ptr<uint8_t[]> data(new uint8_t[data_len]);
	in.seekg(0, std::ios::beg);
	in.read((char*)data.get(), data_len);
	in.close();

	std::unique_ptr<uint8_t[]> decrypted(nullptr);
	aes_decode(data.get(), data_len, decrypted);

	auto message = MyMessage::UnPackMessage(decrypted.get());
	std::cout
		<< "\n## Decode"
		<< "\nid: " << message->id
		<< "\nName: " << message->name
		<< "\nContent: '" << message->content << "'\n"
		<< message->bindata[0] + message->bindata[1] + message->bindata[3]
		<< std::endl;
}

int main()
{
	step1_write();
	step2_read();
	return 0;
}
