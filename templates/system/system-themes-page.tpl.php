<?php

/**
 * @file
 * Default template to display the Appearance page.
 *
 * Available variables:
 * - $themes: An associative array containing groups of themes. Each theme
 *   contains the following keys:
 *   - name: The human-readable name supplied with the theme. This will also
 *     contain the theme version and any notes about the theme, such as if this
 *     is the default theme.
 *   - description: The description supplied with the theme.
 *   - screenshot: The themed screenshot supplied with the theme.
 *   - incompatibility: FALSE if the theme is compatible with both Drupal core
 *     version and PHP version, or a compatibility message to display.
 *   - links: Themed links for enabling/disabling/uninstalling the theme. Also
 *     contains a link to the theme settings if the theme is either installed or
 *     set as the administration theme.
 */
?>
<div id="system-themes-page">
  <?php foreach ($theme_group_titles as $state => $title): ?>
    <?php if (!count($themes[$state])) {
      // Skip this group of themes if no theme is there.
      continue;
    } ?>

    <?php if ($state == 'enabled'): ?>
      <div class="system-themes-list system-themes-list-<?php print $state; ?> uk-grid">
        <h2 class="uk-margin"><?php print $title; ?></h2>

        <?php foreach ($themes[$state] as $theme): ?>
          <div class="uk-width-1-1 uk-margin-bottom">
            <?php print $theme['screenshot']; ?>
            <div class="theme-information">
              <h3 class="uk-text-bold"><?php print $theme['name']; ?></h3>
              <p><?php print $theme['description']; ?></p>

              <?php if ($theme['incompatibility']): ?>
                <p><?php print $theme['incompatibility']; ?></p>
              <?php endif; ?>

              <?php print $theme['links']; ?>
            </div>
          </div>
        <?php endforeach; ?>

      </div>

      <?php if (count($themes['disabled'])): ?>
        <hr class="uk-article-divider">
      <?php endif; ?>

    <?php else: ?>
      <div class="system-themes-list system-themes-list-<?php print $state; ?> uk-grid uk-grid-match uk-margin-bottom" data-uk-grid-match="{target:'.uk-panel'}">
        <h2 class="uk-margin uk-width-1-1"><?php print $title; ?></h2>

        <?php foreach ($themes[$state] as $theme): ?>
          <div class="theme-selector uk-width-small-1-1 uk-width-medium-1-3 uk-width-large-1-5">
            <div class="uk-panel uk-panel-box uk-admin-theme-selector-panel-box">
              <div class="uk-panel-teaser">
                <?php print $theme['screenshot']; ?>
              </div>

              <div class="theme-information">
                <h3 class="uk-panel-title"><?php print $theme['name']; ?></h3>
                <p><?php print $theme['description']; ?></p>

                <?php if ($theme['incompatibility']): ?>
                  <p><?php print $theme['incompatibility']; ?></p>
                <?php endif; ?>

                <?php print $theme['links']; ?>
              </div>
            </div>
          </div>
        <?php endforeach; ?>

      </div>
    <?php endif; ?>
  <?php endforeach; ?>
</div>
