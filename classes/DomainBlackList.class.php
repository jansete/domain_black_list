<?php

class DomainBlackList extends Entity {

  protected function defaultLabel() {
    return $this->domain;
  }

  public static function isDuplicated($domain_name) {

  }

  public static function isValid($domain_name) {

  }
}