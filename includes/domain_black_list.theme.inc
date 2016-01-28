<?php

function domain_black_list_theme($existing, $type, $theme, $path) {
  $path .= '/theme';
  return array(
    'dbl_example_1' => array(
      'template' => 'dbl-example-1',
      'path' => $path,
    ),
    'dbl_example_2' => array(
      'template' => 'dbl-example-2',
      'path' => $path,
    ),
  );
}