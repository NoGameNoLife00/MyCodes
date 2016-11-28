package com.test.controller;

import com.test.authorization.annotation.Authorization;
import com.test.authorization.annotation.CurrentUser;
import com.test.authorization.manager.TokenManager;
import com.test.authorization.model.TokenModel;
import com.test.config.ResultStatus;
import com.test.model.ResultModel;
import com.test.model.UserModel;
import com.test.service.impl.UserServiceImpl;
import com.wordnik.swagger.annotations.Api;
import com.wordnik.swagger.annotations.ApiImplicitParam;
import com.wordnik.swagger.annotations.ApiImplicitParams;
import com.wordnik.swagger.annotations.ApiOperation;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.io.IOException;

@RestController
@RequestMapping("/api/user")
@Api(value = "user-api", description = "用户有关操作")
public class LoginController {

    @Autowired
    private UserServiceImpl userService;

    @Autowired
    private TokenManager tokenManager;

    @RequestMapping(value = "/login", method = RequestMethod.POST)
    @ApiOperation(value = "login")
    public ResponseEntity<ResultModel> login(@RequestBody UserModel userData) throws IOException {

        UserModel user = userService.findUserByName(userData.getUsername());
        if (user == null || !user.getPassword().equals(userData.getPassword())) {
            return new ResponseEntity<ResultModel>(ResultModel.error(
                    ResultStatus.USERNAME_OR_PASSWORD_ERROR), HttpStatus.NOT_FOUND);
        }
        // 生成Token 保存登录状态
        TokenModel model = tokenManager.createToken(user.getUsername());
        return new ResponseEntity<ResultModel>(ResultModel.ok(model), HttpStatus.OK);
    }


    @RequestMapping(value = "/logout", method = RequestMethod.POST)
    @Authorization
    @ApiOperation(value = "logout")
    @ApiImplicitParams({
            @ApiImplicitParam(name = "authorization", value = "authorization", required = true, dataType = "string", paramType = "header"),
    })
    public ResponseEntity<ResultModel> logout(@CurrentUser UserModel user) {
        tokenManager.deleteToken(user.getUsername());
        return new ResponseEntity<ResultModel>(ResultModel.ok(), HttpStatus.OK);
    }
}
