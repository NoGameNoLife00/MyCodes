package com.test.authorization.manager;

import com.test.authorization.model.TokenModel;
import com.test.config.Constants;
import org.springframework.stereotype.Component;
import org.springframework.util.StringUtils;


import java.util.Hashtable;
import java.util.Map;
import java.util.UUID;

/**
 *
 */
@Component
public class TokenManager {

    private Map<String, String> tokenMap = new Hashtable<String, String>();
    private Map<String, Integer> expiresMap = new Hashtable<String, Integer>();

    public TokenModel createToken(String userName) {
        // 使用uuid作为源token
        String token = UUID.randomUUID().toString().replace("-", "");
        TokenModel model = new TokenModel(userName, token);
        //存储过期时间
        tokenMap.put(userName, token);
        expiresMap.put(userName, Constants.TOKEN_EXPIRES_HOUR);
        return model;
    }

    public TokenModel getToken(String authenication) {
        if (authenication == null || authenication.length() == 0) {
            return null;
        }

        String[] param = authenication.split("_");
        if (param.length != 2) {
            return null;
        }

        String userName = param[0];
        String token = param[1];
        return new TokenModel(userName, token);
    }

    public boolean checkToken(TokenModel model) {
        if (model == null) {
            return false;
        }

        String token = tokenMap.get(model.getUsername());
        if (token == null || !token.equals(model.getToken())) {
            return false;
        }
        //如果验证成功，说明此用户进行了一次有效操作，延长token的过期时间
        expiresMap.put(model.getUsername(), Constants.TOKEN_EXPIRES_HOUR);
        return true;
    }

    public void deleteToken(String userName) {
        if (StringUtils.isEmpty(userName)) {
            return;
        }
        tokenMap.remove(userName);
        expiresMap.remove(userName);
    }

}
