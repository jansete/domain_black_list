<?php

class DomainBlackListController extends EntityAPIController {

  public function create(array $values = array()) {
    global $user;
    $values += array(
      'domain' => '',
      'status' => 1,
      'uid' => $user->uid,
      'description' => '',
    );
    return parent::create($values);
  }
}