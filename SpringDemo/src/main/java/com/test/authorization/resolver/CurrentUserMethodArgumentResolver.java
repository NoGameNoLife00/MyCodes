package com.test.authorization.resolver;

import com.test.authorization.annotation.CurrentUser;
import com.test.config.Constants;
import com.test.model.UserModel;
import com.test.service.impl.UserServiceImpl;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.core.MethodParameter;
import org.springframework.stereotype.Component;
import org.springframework.web.bind.support.WebDataBinderFactory;
import org.springframework.web.context.request.NativeWebRequest;
import org.springframework.web.context.request.RequestAttributes;
import org.springframework.web.method.support.HandlerMethodArgumentResolver;
import org.springframework.web.method.support.ModelAndViewContainer;
import org.springframework.web.multipart.support.MissingServletRequestPartException;

/**
 * 方法注入，将含有CurrentUser注解的方法参数注入当前登录用户
 */
@Component
public class CurrentUserMethodArgumentResolver implements HandlerMethodArgumentResolver {

    @Autowired
    private UserServiceImpl userService;

    @Override
    public boolean supportsParameter(MethodParameter parameter) {
        // 如果参数是UserModel 并且有CurrentUser注释
        if (parameter.getParameterType().isAssignableFrom(UserModel.class) &&
                parameter.hasParameterAnnotation(CurrentUser.class)) {
            return true;
        }
        return false;
    }

    @Override
    public Object resolveArgument(MethodParameter parameter, ModelAndViewContainer mavContainer, NativeWebRequest webRequest, WebDataBinderFactory binderFactory) throws Exception {
        // 取出鉴权时存入的登录用户名
        String currentUserName = (String)webRequest.getAttribute(Constants.CURRENT_USER_NAME, RequestAttributes.SCOPE_REQUEST);
        if (currentUserName != null) {
            return userService.findUserByName(currentUserName);
        }
        throw new MissingServletRequestPartException(Constants.CURRENT_USER_NAME);
    }
}
