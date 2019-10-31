/*
 * Copyright 2009-2017 Alibaba Cloud All rights reserved.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <alibabacloud/kms/KmsClient.h>
#include <alibabacloud/core/SimpleCredentialsProvider.h>
#include <alibabacloud/core/Utils.h>

using namespace AlibabaCloud;
using namespace AlibabaCloud::Location;
using namespace AlibabaCloud::Kms;
using namespace AlibabaCloud::Kms::Model;

namespace
{
	const std::string SERVICE_NAME = "Kms";
}
std::shared_ptr<KmsClient> KmsClient::CreateKmsClient(const std::string token, const int connectTimeout, const int readTimeout)
{
	std::string base64Decode = Base64Decode(token);
	if(base64Decode.empty()) return nullptr;
	std::map<std::string, std::string> paramsMap = JsonToMap(base64Decode); 
	if(paramsMap.empty() 
		|| paramsMap.find("regionId") == paramsMap.end() 
		|| paramsMap.find("accessKeyId") == paramsMap.end()
		|| paramsMap.find("accessKeySecret") == paramsMap.end()
		|| paramsMap.find("securityToken") == paramsMap.end()
	) return nullptr;
	ClientConfiguration configuration(paramsMap["regionId"]);
	configuration.setConnectTimeout(connectTimeout);
	configuration.setReadTimeout(readTimeout);
	Credentials credentials(paramsMap["accessKeyId"], paramsMap["accessKeySecret"], paramsMap["securityToken"]);
	return std::shared_ptr<KmsClient>(new KmsClient(credentials, configuration));
}

KmsClient::KmsClient(const Credentials &credentials, const ClientConfiguration &configuration) :
	RpcServiceClient(SERVICE_NAME, std::make_shared<SimpleCredentialsProvider>(credentials), configuration)
{
	auto locationClient = std::make_shared<LocationClient>(credentials, configuration);
	endpointProvider_ = std::make_shared<EndpointProvider>(locationClient, configuration.regionId(), SERVICE_NAME, "kms");
}

KmsClient::~KmsClient()
{}

KmsClient::DecryptOutcome KmsClient::decrypt(const DecryptRequest &request) const
{
	auto endpointOutcome = endpointProvider_->getEndpoint();
	if (!endpointOutcome.isSuccess())
		return DecryptOutcome(endpointOutcome.error());

	auto outcome = makeRequest(endpointOutcome.result(), request);

	if (outcome.isSuccess())
		return DecryptOutcome(DecryptResult(outcome.result()));
	else
		return DecryptOutcome(outcome.error());
}

void KmsClient::decryptAsync(const DecryptRequest& request, const DecryptAsyncHandler& handler, const std::shared_ptr<const AsyncCallerContext>& context) const
{
	auto fn = [this, request, handler, context]()
	{
		handler(this, request, decrypt(request), context);
	};

	asyncExecute(new Runnable(fn));
}

KmsClient::DecryptOutcomeCallable KmsClient::decryptCallable(const DecryptRequest &request) const
{
	auto task = std::make_shared<std::packaged_task<DecryptOutcome()>>(
			[this, request]()
			{
			return this->decrypt(request);
			});

	asyncExecute(new Runnable([task]() { (*task)(); }));
	return task->get_future();
}
