package com.test.model;

import java.io.Serializable;

public class UserModel implements Serializable {
	String username;
    String password;

    public UserModel() {

    }
    public UserModel(String username, String password) {
        this.username = username;
        this.password = password;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

}
