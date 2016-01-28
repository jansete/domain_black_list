<h2><?php print t('This is an example for "Remove url from link"'); ?></h2>
<div>
  <?php foreach ($links as $url => $text): ?>
    <?php print $text . ': ' .l($text, $url, array(
        'external' => TRUE,
        'absolute' => TRUE,
        'attributes' => array('target' => '_blank')));
    ?><br />
  <?php endforeach; ?>
</div>