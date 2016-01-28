<?php

/**
 * Preprocess for example 1: Show message if feature is disabled.
 */
function template_preprocess_dbl_example_1(&$vars) {
  if (!variable_get('domain_black_list_filter_html_page')) {
    DomainBlackListFilter::showDisableFeatureMessage();
  }
}

/**
 * Preprocess for example 2: Show message if feature is disabled and prepare
 * links.
 */
function template_preprocess_dbl_example_2(&$vars) {
  if (!variable_get('domain_black_list_alter_urls')) {
    DomainBlackListFilter::showDisableFeatureMessage();
  }

  $vars['links'] = array(
    'http://google.es' => t('Google Spain'),
    'http://google.pl' => t('Google Poland'),
    'http://google.mx' => t('Google Mexico'),
  );
}