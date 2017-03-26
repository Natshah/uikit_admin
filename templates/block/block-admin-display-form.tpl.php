<?php

/**
 * @file
 * UIkit's theme implementation to display the configure blocks form.
 *
 * Available variables:
 * - $block_regions: An array of regions. Keyed by name with the title as value.
 * - $block_listing: An array of blocks keyed by region and then delta.
 * - $form_submit: Form submit button.
 *
 * Each $block_listing[$region] contains an array of blocks for that region.
 *
 * Each $data in $block_listing[$region] contains:
 * - $data->region_title: Region title for the listed block.
 * - $data->block_title: Block title.
 * - $data->region_select: Drop-down menu for assigning a region.
 * - $data->weight_select: Drop-down menu for setting weights.
 * - $data->configure_link: Block configuration link.
 * - $data->delete_link: For deleting user added blocks.
 *
 * @see template_preprocess_block_admin_display_form()
 * @see theme_block_admin_display()
 *
 * @ingroup uikit_themeable
 */
?>
<?php
  // Add table javascript.
  $uikit = drupal_get_path('theme', 'uikit');
  drupal_add_js($uikit . '/js/tableheader.js');
  drupal_add_js(drupal_get_path('module', 'block') . '/block.js');
  foreach ($block_regions as $region => $title) {
    drupal_add_tabledrag('blocks', 'match', 'sibling', 'block-region-select', 'block-region-' . $region, NULL, FALSE);
    drupal_add_tabledrag('blocks', 'order', 'sibling', 'block-weight', 'block-weight-' . $region);
  }
?>
<div class="uk-overflow-container">
  <table id="blocks" class="uk-table uk-table-hover uk-text-nowrap sticky-enabled">
    <thead>
      <tr>
        <th><?php print t('Block'); ?></th>
        <th><?php print t('Region'); ?></th>
        <th><?php print t('Weight'); ?></th>
        <th colspan="2"><?php print t('Operations'); ?></th>
      </tr>
    </thead>
    <tbody>
      <?php $row = 0; ?>
      <?php foreach ($block_regions as $region => $title): ?>
        <tr class="region-title region-title-<?php print $region?>">
          <td colspan="5"><?php print $title; ?></td>
        </tr>
        <tr class="region-message region-<?php print $region?>-message <?php print empty($block_listing[$region]) ? 'region-empty' : 'region-populated'; ?>">
          <td colspan="5"><em class="uk-text-danger"><?php print t('No blocks in this region'); ?></em></td>
        </tr>
        <?php foreach ($block_listing[$region] as $delta => $data): ?>
        <tr class="draggable <?php print $row % 2 == 0 ? 'odd' : 'even'; ?><?php print $data->row_class ? ' ' . $data->row_class : ''; ?>">
          <td class="block"><?php print $data->block_title; ?></td>
          <td><?php print $data->region_select; ?></td>
          <td><?php print $data->weight_select; ?></td>
          <td><?php print $data->configure_link; ?></td>
          <td><?php print $data->delete_link; ?></td>
        </tr>
        <?php $row++; ?>
        <?php endforeach; ?>
      <?php endforeach; ?>
    </tbody>
  </table>
</div>

<?php print $form_submit; ?>
