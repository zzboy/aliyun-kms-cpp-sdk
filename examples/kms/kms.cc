#include <iostream>
#include "alibabacloud/core/AlibabaCloud.h"
#include "alibabacloud/kms/KmsClient.h"

using namespace std;
using namespace AlibabaCloud;
using namespace AlibabaCloud::Kms;

int main() {
  InitializeSdk();
  std::shared_ptr<KmsClient> kmsClient = KmsClient::CreateKmsClient("eyJyZWdpb25JZCI6ImNuLWhhbmd6aG91IiwgImFjY2Vzc0tleUlkIjoiU1RTLk5SWEx5RDV2WUQ3S2JTUmRwS3BuZEJwV2ciLCAiYWNjZXNzS2V5U2VjcmV0IjoiSjZxRkU5SGczY3FUQU16ZXpqZWtSNDRtNURGTnJrN0dqVFZyZXdiZWdoQmoiLCAic2VjdXJpdHlUb2tlbiI6IkNBSVM5QUYxcTZGdDVCMnlmU2pJcjVIdEI4UHcyS2w0OC9XZ1lIWGpnSEFlZk9GSXJiWDhoVHoySUhsT2ZYVmdBdXNadC9zeG4ydFQ3UDhjbHFweWJLUWRsYm8zZ1VFMXZQcHQ2Z3FFVDlmcm1hN2N0TTRwNnZDTUhXeVVGR1NJdnF2N2FQbjRTOVh3WStxa2IwdSsrQVo0M2JyOWMwZkpQVFhuUytycjc2UnFkZE1LUkFLMVFDTmJEZE5OWEd0WXBkUWRLR0hhT0lUR1VIZW9vQktKVWhNMDRGc2owVG9rdVBubG1KWE0wSGVFMGcybWtOMXlqcC9xUDUycFkvTnJPSnBDU05xdjFJUjBEUEdZaW5jTXUwTVJxLzRwMHZjZm9tMmU0TXZuRDFoWDdBbVBOK21SK014b0wwcGpZYXczQzArVFprTkNQZ0VUR29BQmhvYUpQOXdiSWpzVTBPOUlMaTFqSUhiQkIzUHVLWDZmTFRld3RTSm9mTHVLUGI5eDI4TVV6eFhBSytHVENUd3ZsdXQ3bXo0MzVrRHBEVThHYVdxMGVzdEdSRm1IamwwNndpbHBQWXVLYjhVME9BN05GeU1JcDk5bkhxRHR0NS8wKzVmai9wT0d2dFg2dUJUbytuaW91MUFQbzdGSUtid2ZBTDdCNUx1UnpPND0ifQ==");
  Model::DecryptRequest decryptRequest;
  decryptRequest.setEncryptionContext("{\"biz\":\"dingding\"}");
  decryptRequest.setCiphertextBlob("ZjRhMWVmY2ItZjljYS00MTkwLWE0YjktNzcyYTJiZjhlMzgxazBodUJ2K3BVaUdVVisrK0lFQitwTktpYTJVR3d0ZnRBQUFBQUFBQUFBQ1p6VEcxTStzbklFMk4wQ2RHOG8yeDBCTytmb0Jpa2JXM2w3K0ZIamdoOUdMWnJLSXpSUWpP");
  auto outcome = kmsClient->decrypt(decryptRequest);
  cout << endl << "kms decrypt returned:" << endl;
  cout << "error code: " << outcome.error().errorCode() << endl;
  cout << "keyId: " << outcome.result().getKeyId() << endl << endl;
  cout << "plainText: " << outcome.result().getPlaintext() << endl << endl;
  cout << "KeyVersion: " << outcome.result().getKeyVersionId() << endl << endl;

  ShutdownSdk();
}
