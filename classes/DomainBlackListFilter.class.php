<?php

class DomainBlackListFilter {

  public static function removeDomainFromString($domains_patterns, &$string) {
    self::replaceDomainFromString($domains_patterns, $string);
  }

  public static function replaceDomainFromString($domains_patterns, &$string, $replace = '', $type = 'filter_html_page') {
    $count = 0;
    $string = preg_replace($domains_patterns, $replace, $string, -1, $count);

    if (variable_get('domain_black_list_debug')) {
      switch ($type) {
        case 'filter_html_page':
          $message = format_plural($count, t('1 domain was removed in the previous request ("Remove domains from HTML output").'),
            t('@count domains were removed in the previous request ("Remove domains from HTML output").'));
          break;
        case 'alter_urls':
          $message = format_plural($count, t('1 domain was removed in the current request from the href HTML attribute ("Remove url from link").'),
            t('@count domains were removed in the current request from the href HTML attribute ("Remove url from link").'));
          break;
        default:
          $message = t('Debug is enabled');
      }

      self::showDebugMessage($message);
    }
  }

  /**
   * If debug mode is enable, show debug information like a status message.
   */
  public static function showDebugMessage($message) {
    if (user_access(ADMINISTER_DOMAINS_BLACK_LIST_ENTITIES_PERM)) {
      drupal_set_message($message);
    }
  }

  public static function formatDomains(&$domains, $type = 'filter_html_page') {
    $result = array();
    $types = self::getTypes();

    foreach ($domains as $domain) {
      $result[] = call_user_func_array($types[$type]['callback'], array($domain));
    }

    $domains = $result;
  }

  public static function getFullHTMLPattern($domain) {
    return '/<a\s+(?:[^>]*?\s+)?href="http\:\/\/' . str_replace('.', '\\.', $domain) . '(.*?)"(.*?)>(.*?)<\/a>/im';
  }

  public static function getAlterUrlsPattern($domain) {
    return $domain ? '/' . str_replace('.', '\\.', $domain) . '/i' : FALSE;
//    return '/http\:\/\/' . str_replace('.', '\\.', $domain) . '(.*?)/im';
  }

  public static function getTypes() {
    return array(
      'filter_html_page' => array(
        'callback' => 'DomainBlackListFilter::getFullHTMLPattern',
      ),
      'alter_urls' => array(
        'callback' => 'DomainBlackListFilter::getAlterUrlsPattern',
      )
    );
  }

  /**
   * Get field types where validate it.
   * @todo create hook for extends with others modules
   */
  public static function getValidateFieldTypes() {
    return array(
      'text_long',
      'text_with_summary',
    );
  }

  /**
   *  Get fields instances that belong in validate field types array in an
   *  entity.
   */
  public static function getValidateFieldsInstancesFromEntity($entity_type, $bundle) {
    $validate_fields = self::getValidateFieldTypes();

    $query = db_select('field_config_instance', 'fci');
    $query->innerJoin('field_config', 'fc', 'fc.field_name = fci.field_name');
    $query->fields('fci', array('field_name'));
    $query->condition('fci.entity_type', $entity_type)
      ->condition('fci.bundle', $bundle)
      ->condition('fc.type', $validate_fields, 'IN');
    return $query->execute()->fetchAll();
  }

//  public static function getScapedChars() {
//    return array(
//      '\\',
//      '^',
//      '$',
//      '.',
//      '[',
//      ']',
//      '|',
//      '(',
//      ')',
//      '?',
//    );
//  }
}