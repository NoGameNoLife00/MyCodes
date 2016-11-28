package com.test.authorization.annotation;

import java.lang.annotation.*;

/**
 * 在Controller的方法上使用此注解，该方法在映射时会检查用户是否登录，未登录返回401错误
 */
@Documented
@Inherited
@Target(ElementType.METHOD)
@Retention(RetentionPolicy.RUNTIME)
public @interface Authorization {

}
