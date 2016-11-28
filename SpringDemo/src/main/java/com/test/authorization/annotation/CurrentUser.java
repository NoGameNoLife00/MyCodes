package com.test.authorization.annotation;

import java.lang.annotation.*;

/**
 * 在Controller的方法参数中使用此注解，该方法在映射时会注入当前登录的User对象
 */
@Documented
@Inherited
@Target(ElementType.PARAMETER)
@Retention(RetentionPolicy.RUNTIME)
public @interface CurrentUser {
}
